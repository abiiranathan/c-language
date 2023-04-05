// pdfsearch.c
// Usage: ./pdfsearch mypdf.pdf "niddle" 60
// 60 is the context length to include around each match.
// You can use regex as a pattern as well.
// Author: Dr. Abiira Nathan<nabiira2by2@gmail.com>
// Date: 2023-04-05

#include <locale.h>
#include <poppler/glib/poppler.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define CONTEXT_SIZE 50
#define MAX_THREADS 20

typedef struct search_args {
    PopplerDocument *doc;
    char *search_term;
    int start_page;
    int end_page;
    int context_size;
} search_args;

void *search_thread(void *args) {
    search_args *search_args = (struct search_args *)args;

    // create case-insensitive regex pattern
    GRegex *regex = g_regex_new(search_args->search_term, G_REGEX_CASELESS, 0, NULL);

    // iter over each page in range
    for (int page_num = search_args->start_page; page_num < search_args->end_page; page_num++) {
        PopplerPage *page = poppler_document_get_page(search_args->doc, page_num);
        if (page == NULL) {
            printf("Error: could not get page: %d\n", page_num);
            continue;
        }

        // extract text content from the page
        gchar *text = poppler_page_get_text(page);

        // convert unicode char to utf-8
        wchar_t *wtext = calloc(strlen(text) + 1, sizeof(wchar_t));
        mbstowcs(wtext, text, strlen(text));

        char *utf8_text = calloc((strlen(text) * 4) + 1, sizeof(char));
        wcstombs(utf8_text, wtext, strlen(text) * 4);

        // search for the target search term using regex
        GMatchInfo *match_info;
        if (g_regex_match(regex, utf8_text, 0, &match_info)) {
            // Print every matching word and context before and after it.
            while (g_match_info_matches(match_info)) {
                int start_index, end_index, context_size = CONTEXT_SIZE;

                if (search_args->context_size != -1) {
                    context_size = search_args->context_size;
                }

                // get the indices of the matches
                g_match_info_fetch_pos(match_info, 0, &start_index, &end_index);
                int match_size = end_index - start_index;

                int start_context = (start_index > context_size) ? start_index - context_size : 0;
                int end_context = ((strlen(utf8_text) - end_index) > context_size) ? end_index + context_size : strlen(utf8_text);
                gchar *match_text = g_strndup(&utf8_text[start_context], end_context - start_context);

                // Convert to Unicode
                size_t len = strlen(match_text) + 1;                   // length of the string, plus null terminator
                wchar_t *unicode_text = calloc(len, sizeof(wchar_t));  // allocate memory for the converted string
                if (unicode_text == NULL) {
                    printf("Error: Calloc() failed to allocate memory for unicode text\n");
                    continue;
                }

                mbstowcs(unicode_text, match_text, len);  // convert the string
                if (unicode_text == NULL) {
                    printf("Error: Calloc() failed to convert text to unicode\n");
                    continue;
                }

                // Print the context and highlight the match
                wprintf(L"_____________ Page: %d ___________________\n", page_num + 1);
                for (int i = start_context; i < end_context; i++) {
                    if (i >= start_index && i < end_index) {
                        wprintf(L"\033[47;31m%lc\033[0m", unicode_text[i - start_context]);
                    } else {
                        wprintf(L"%lc", unicode_text[i - start_context]);
                    }
                }
                wprintf(L"\n\n");

                // Free memory
                g_free(match_text);
                free(unicode_text);
                g_match_info_next(match_info, NULL);
            }
        }

        // Clean up
        g_free(text);
        g_match_info_free(match_info);

        free(wtext);
        free(utf8_text);

        // free memory usage by page object
        g_object_unref(page);
    }

    g_regex_unref(regex);
    return NULL;
}

int main(int argc, char const *argv[]) {
    if (argc < 3) {
        printf("Usage: %s filename search term\n", argv[0]);
        return EXIT_FAILURE;
    }

    // set the locale to the user's default to handle Unicode characters correctly
    setlocale(LC_ALL, "");

    GFile *file = g_file_new_for_path(argv[1]);
    GError *error = NULL;
    GBytes *bytes = g_file_load_bytes(file, NULL, NULL, &error);

    if (bytes == NULL) {
        g_print("Error: %s\n", error->message);

        g_error_free(error);
        g_object_unref(file);
        return EXIT_FAILURE;
    }

    // Create PDF Document object.
    error = NULL;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, NULL, &error);
    if (doc == NULL) {
        g_print("Error creating document: %s\n", error->message);
        g_error_free(error);
        g_bytes_unref(bytes);
        g_object_unref(file);
        return EXIT_FAILURE;
    }

    // Get the number of pages in the PDF Document.
    int num_pages = poppler_document_get_n_pages(doc);

    // split pages into multiple ranges for multi-threading
    int num_threads = MAX_THREADS;
    if (num_pages < MAX_THREADS) {
        num_threads = num_pages;
    }

    int pages_per_thread = num_pages / num_threads;

    search_args *thread_args = calloc(num_threads, sizeof(search_args));
    if (!thread_args) {
        printf("unable to calloc() memory for search args");
        return EXIT_FAILURE;
    }

    pthread_t *threads = calloc(num_threads, sizeof(pthread_t));
    if (!threads) {
        printf("unable to allocate memory to threads");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < num_threads; i++) {
        thread_args[i].doc = doc;
        thread_args[i].search_term = (char *)argv[2];
        thread_args[i].start_page = i * pages_per_thread;
        thread_args[i].context_size = argc > 3 ? atoi(argv[3]) : -1;

        // If we are the last page, this is the end page.
        if (i == (num_pages - 1)) {
            thread_args[i].end_page = num_pages;
        } else {
            thread_args[i].end_page = (i + 1) * pages_per_thread;
        }

        // Create and start the threads, passing off the search function with arguments
        int result = pthread_create(&threads[i], NULL, search_thread, (void *)&thread_args[i]);
        if (result != 0) {
            printf("Error: could not create thread %d\n", i);
            return EXIT_FAILURE;
        }
    }

    // wait for all the threads to complete
    for (int i = 0; i < num_threads; i++) {
        int result = pthread_join(threads[i], NULL);
        if (result != 0) {
            printf("Error: could not join thread: %d\n", i);
            return EXIT_FAILURE;
        }
    }

    // free memory used by thread arguments and thread objects
    free(thread_args);
    free(threads);

    // Free the file
    g_object_unref(file);

    // Free the bytes
    g_bytes_unref(bytes);

    // Free memory used by the PDF document object.
    g_object_unref(doc);

    return EXIT_SUCCESS;
}
