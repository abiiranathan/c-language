#include "../include/str.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct String {
    char *data;    /** Pointer to the character array */
    size_t size;   /** Size of the character array */
    size_t length; /** Length of the string */
} String;

// Initial size of the character array.
#define INIT_SIZE 16

char *string_duplicate(const char *str) {
    size_t len = strlen(str) + 1;
    char *new_str = malloc(len);
    if (new_str) {
        memcpy(new_str, str, len);
    }
    return new_str;
}

/**
 * Allocates memory for a new String structure and initializes it with the provided null-terminated string.
 *
 * @param str The null-terminated string to initialize the new String structure with. If NULL is passed, an empty string is created.
 * @return The new String structure that has been allocated and initialized with the provided string, or an empty string if str is NULL.
 * @remark It is the responsibility of the caller to free the memory of the returned structure using string_free().
 */
String *string_new(const char *str) {
    String *s = malloc(sizeof(String));
    if (s == NULL) {
        return NULL;
    }

    s->length = strlen(str);
    s->size = s->length + 1;
    s->data = malloc(s->size);
    if (s->data == NULL) {
        free(s);
        return NULL;
    }
    strncpy(s->data, str, s->size);
    return s;
}

/**
 * Allocates memory for a new String object.
 *
 * @return A pointer to the new String object, or NULL if memory allocation fails.
 */
String *string_init() {
    String *s = malloc(sizeof(String));
    if (s == NULL) {
        return NULL;
    }
    s->data = malloc(INIT_SIZE);
    if (s->data == NULL) {
        free(s);
        return NULL;
    }
    s->size = INIT_SIZE;
    s->length = 0;
    s->data[0] = '\0';
    return s;
}

/**
 * Frees the memory allocated for a String object.
 *
 * @param s A pointer to the String object to be freed.
 */
void string_free(String *s) {
    free(s->data);
    s->data = NULL;

    free(s);
    s = NULL;
}

/**
 * frees the memory allocated for the substrings obtained from the string_split
 * functions.
 */
void string_free_substrings(char **arr, int count) {
    if (!arr) return;

    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

/**
 * Resizes the character array of a String object.
 *
 * @param s A pointer to the String object to be resized.
 * @param new_size The new size of the character array.
 */
void string_resize(String *s, size_t new_size) {
    char *new_data = realloc(s->data, new_size);
    if (new_data != NULL) {
        s->data = new_data;
        s->size = new_size;
    }
}

/**
 * Appends a string to the end of a String object.
 *
 * @param s A pointer to the String object.
 * @param str The string to be appended.
 */
void string_append(String *src, String *str) {
    if (src->length + str->length + 1 > src->size) {
        size_t new_size = src->size;
        while (src->length + str->length + 1 > new_size) {
            new_size *= 2;
        }
        string_resize(src, new_size);
    }
    strncat(src->data, str->data, str->length);
    src->length += str->length;
}

/**
 * Appends a string to the end of a String object.
 *
 * @param src A pointer to the source String object that will be modified.
 * @param str A character pointer.
 */
void string_append_cstr(String *src, const char *str) {
    size_t str_size = strlen(str);
    if ((src->length + str_size + 1) > src->size) {
        size_t new_size = src->size;
        while (src->length + str_size + 1 > new_size) {
            new_size *= 2;
        }
        string_resize(src, new_size);
    }
    strncat(src->data, str, str_size);
    src->length += str_size;
}

/**
 * Inserts a string into a String object at a specified index.
 *
 * @param s A pointer to the String object.
 * @param str The string to be inserted.
 * @param index The index at which to insert the string.
 */
void string_insert(String *s, const char *str, size_t index) {
    size_t str_len = strlen(str);
    if (s->length + str_len + 1 > s->size) {
        size_t new_size = s->size;
        while (s->length + str_len + 1 > new_size) {
            new_size *= 2;
        }
        string_resize(s, new_size);
    }

    memmove(s->data + index + str_len, s->data + index, s->length - index + 1);
    memcpy(s->data + index, str, str_len);
    s->length += str_len;
}

/**
 * Removes a portion of a string from a String object.
 *
 * @param s A pointer to the String object.
 * @param index The starting index of the portion to be removed.
 * @param count The number of characters to remove.
 */
void string_remove(String *s, size_t index, size_t count) {
    if (index + count >= s->length) {
        s->data[index] = '\0';
        s->length = index;
    } else {
        memmove(s->data + index, s->data + index + count, s->length - index - count + 1);
        s->length -= count;
    }
}

/**
Replaces a portion of a string in a String object with a new string.
@param s A pointer to the String object.
@param index The starting index of the portion to be replaced.
@param count The number of characters to replace.
@param new_str The string to replace the portion with.
*/
void string_replace(String *s, size_t index, size_t count, const char *new_str) {
    size_t new_str_len = strlen(new_str);
    if (count < new_str_len) {
        size_t new_size = s->size;
        while (s->length - count + new_str_len + 1 > new_size) {
            new_size *= 2;
        }
        string_resize(s, new_size);
    }

    memmove(s->data + index + new_str_len, s->data + index + count, s->length - index - count + 1);
    memcpy(s->data + index, new_str, new_str_len);
    s->length += new_str_len;
}

/**
Returns the character at a specified index in a String object.
@param s A pointer to the String object.
@param index The index of the desired character.
@return The character at the specified index.
*/
char string_char_at(String *s, size_t index) {
    if (index < s->length) {
        return s->data[index];
    } else {
        return '\0';
    }
}

/**
Returns a pointer to the character array of a String object.
@param s A pointer to the String object.
@return A pointer to the character array.
*/
char *string_data(String *s) {
    return s->data;
}

/**
Returns the length of a String object.
@param s A pointer to the String object.
@return The length of the string.
*/
size_t string_length(String *s) {
    return s->length;
}

/**
 * Splits a String object into an array of substrings based on a delimiter character.
 *
 * @param s A pointer to the String object.
 * @param delimiter The delimiter character to split the string with.
 * @param count A pointer to an integer to store the number of substrings in the resulting array.
 * @return An array of pointers to the resulting substrings.
 */
char **string_split(String *s, char delimiter, int *count) {
    int num_delimiters = 0;
    for (size_t i = 0; i < s->length; i++) {
        if (s->data[i] == delimiter) {
            num_delimiters++;
        }
    }
    *count = num_delimiters + 1;

    char **result = malloc(*count * sizeof(char *));
    if (!result) {
        return NULL;
    }

    int result_index = 0;
    size_t start_index = 0;
    for (size_t i = 0; i <= s->length; i++) {
        if (i == s->length || s->data[i] == delimiter) {
            size_t substr_length = i - start_index;
            char *substr = malloc((substr_length + 1) * sizeof(char));
            if (!substr) {
                for (int j = 0; j < result_index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(substr, s->data + start_index, substr_length);
            substr[substr_length] = '\0';
            result[result_index] = substr;
            result_index++;
            start_index = i + 1;
        }
    }

    return result;
}

/**
 * Splits a String object into an array of substrings based on a delimiter character, up to a maximum number of substrings.
 *
 * @param s A pointer to the String object.
 * @param delimiter The delimiter character to split the string with.
 * @param max_count The maximum number of substrings to include in the resulting array.
 * @param count A pointer to an integer to store the actual number of substrings in the resulting array.
 * @return An array of pointers to the resulting substrings.
 */
char **string_split_n(String *s, char delimiter, int max_count, int *count) {
    int num_delimiters = 0;
    for (size_t i = 0; i < s->length; i++) {
        if (s->data[i] == delimiter) {
            num_delimiters++;
        }
    }
    *count = (num_delimiters + 1 > max_count) ? max_count : num_delimiters + 1;

    char **result = malloc(*count * sizeof(char *));
    if (!result) {
        return NULL;
    }

    int result_index = 0;
    size_t start_index = 0;
    for (size_t i = 0; i <= s->length && result_index < max_count - 1; i++) {
        if (i == s->length || s->data[i] == delimiter) {
            size_t substr_length = i - start_index;
            char *substr = malloc((substr_length + 1) * sizeof(char));
            if (!substr) {
                for (int j = 0; j < result_index; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(substr, s->data + start_index, substr_length);
            substr[substr_length] = '\0';
            result[result_index] = substr;
            result_index++;
            start_index = i + 1;
        }
    }

    if (result_index < max_count) {
        size_t substr_length = s->length - start_index;
        char *substr = malloc((substr_length + 1) * sizeof(char));

        if (!substr) {
            for (int j = 0; j < result_index; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        memcpy(substr, s->data + start_index, substr_length);
        substr[substr_length] = '\0';
        result[result_index] = substr;
        result_index++;
    }

    return result;
}

/**
Joins an array of substrings into a new String object, separated by a delimiter character.

@param substrings An array of pointers to the substrings to join.
@param count The number of substrings in the array.
@param delimiter The delimiter character to separate the substrings with.
@return A pointer to a new String object that contains the joined substrings.
*/
String *string_join(char **substrings, int count, char delimiter) {
    size_t total_length = 0;
    for (int i = 0; i < count; i++) {
        total_length += strlen(substrings[i]) + 1;
    }

    if (total_length == 0) {
        return NULL;
    }

    char *data = malloc(total_length * sizeof(char));
    if (!data) {
        return NULL;
    }

    size_t index = 0;
    for (int i = 0; i < count; i++) {
        size_t substr_length = strlen(substrings[i]);
        memcpy(data + index, substrings[i], substr_length);
        index += substr_length;
        if (i < count - 1) {
            data[index] = delimiter;
            index++;
        }
    }
    data[index] = '\0';

    String *result = string_new(data);
    free(data);
    return result;
}

/**

Returns a substring of a String object starting at a specified index and ending at a specified index.

@param s A pointer to the String object.
@param start The starting index of the substring.
@param end The ending index of the substring.
@return A pointer to a new String object that contains the specified substring.
*/
String *string_substring(String *s, size_t start, size_t end) {
    if (start >= s->length || end < start) {
        return NULL;
    }

    if (end >= s->length) {
        end = s->length - 1;
    }

    size_t substr_length = end - start + 1;
    char *substr = malloc((substr_length + 1) * sizeof(char));
    if (!substr) {
        return NULL;
    }

    memcpy(substr, s->data + start, substr_length);
    substr[substr_length] = '\0';

    String *result = string_new(substr);
    free(substr);
    return result;
}

/**
 * Appends a specified number of characters to the end of a String object.
 *
 * @param s A pointer to the String object.
 * @param data A pointer to the string to append.
 * @param len The number of characters to append.
 * @return 1 if successful, 0 otherwise.
 */
int string_append_len(String *s, const char *data, int len) {
    if (!s || !data || len < 0) {
        return 0;
    }

    size_t new_length = s->length + len;
    char *new_data = realloc(s->data, (new_length + 1) * sizeof(char));
    if (!new_data) {
        return 0;
    }

    memcpy(new_data + s->length, data, len);
    new_data[new_length] = '\0';

    s->data = new_data;
    s->length = new_length;

    return 1;
}

/**
 * Returns the index of the first occurrence of a substring in a String object,
 * starting from a specified position. Returns -1 if the substring is not found.
 *
 * @param s A pointer to the String object.
 * @param substr The substring to search for.
 * @param start_index The starting position of the search.
 * @return The index of the first occurrence of the substring, or -1 if not found.
 */
int string_index_of(String *s, const char *substr, int start_index) {
    if (!s || !substr || start_index < 0 || start_index >= (int)s->length) {
        return -1;
    }

    int substr_length = strlen(substr);
    if (substr_length == 0) {
        return start_index;
    }

    for (int i = start_index; i <= (int)(s->length - substr_length); i++) {
        int j;
        for (j = 0; j < substr_length; j++) {
            if (s->data[i + j] != substr[j]) {
                break;
            }
        }
        if (j == substr_length) {
            return i;
        }
    }
    return -1;
}

/**
Replaces all occurrences of a substring in a String object with another substring.
@param s A pointer to the String object.
@param old_substr The substring to replace.
@param new_substr The substring to replace with.
@return A pointer to a new String object that contains the modified string.
*/
String *string_replace_all(String *s, const char *old_substr, const char *new_substr) {
    String *result = string_new("");
    if (!result) {
        return NULL;
    }

    int start_index = 0;
    size_t old_substr_length = strlen(old_substr);

    while (start_index < (int)s->length) {
        int match_index = string_index_of(s, old_substr, start_index);
        if (match_index == -1) {
            string_append_cstr(result, s->data + start_index);
            break;
        }
        string_append_len(result, s->data + start_index, match_index - start_index);
        string_append_cstr(result, new_substr);
        start_index = match_index + old_substr_length;
    }
    return result;
}

/**
Converts all lowercase characters in a String object to uppercase.
@param s A pointer to the String object.
@return A pointer to a new String object that contains the converted string.
*/
String *string_to_upper(String *s) {
    char *data = malloc((s->length + 1) * sizeof(char));
    if (!data) {
        return NULL;
    }

    for (int i = 0; i < (int)s->length; i++) {
        char c = s->data[i];
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
        data[i] = c;
    }
    data[s->length] = '\0';

    String *result = string_new(data);
    free(data);
    return result;
}

/**

Converts all uppercase characters in a String object to lowercase.
@param s A pointer to the String object.
@return A pointer to a new String object that contains the converted string.
*/
String *string_to_lower(String *s) {
    char *data = malloc((s->length + 1) * sizeof(char));
    if (!data) {
        return NULL;
    }

    for (int i = 0; i < (int)s->length; i++) {
        char c = s->data[i];
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
        data[i] = c;
    }
    data[s->length] = '\0';
    String *result = string_new(data);
    free(data);
    return result;
}

/**
 * Reverses the characters in a String object in place.
 * It has a time complexity of O(n/2) and a space complexity of O(1).
 * @param s A pointer to the String object.
 */
void string_reverse(String *s) {
    if (!s || s->length <= 1) {
        return;
    }

    for (int i = 0, j = ((int)s->length - 1); i < j; i++, j--) {
        char temp = s->data[i];
        s->data[i] = s->data[j];
        s->data[j] = temp;
    }
}

/**
 * Creates a new String object that is a copy of an existing String object.
 *
 * @param s A pointer to the String object to clone.
 * @return A pointer to the new String object, or NULL if memory allocation fails.
 */
String *string_clone(String *s) {
    if (!s) {
        return NULL;
    }
    String *clone = string_new(s->data);
    if (!clone) {
        return NULL;
    }
    return clone;
}

/**
 * Checks if a String object starts with a specified prefix.
 *
 * @param s A pointer to the String object.
 * @param prefix A pointer to the prefix string.
 * @return 1 if the String object starts with the prefix, or 0 otherwise.
 */
int string_startswith(String *s, const char *prefix) {
    if (!s || !prefix) {
        return 0;
    }

    size_t prefix_len = strlen(prefix);
    if (prefix_len > s->length) {
        return 0;
    }
    return strncmp(s->data, prefix, prefix_len) == 0;
}

/**
 * Checks if a String object ends with a specified suffix.
 *
 * @param s A pointer to the String object.
 * @param suffix A pointer to the suffix string.
 * @return 1 if the String object ends with the suffix, or 0 otherwise.
 */
int string_endswith(String *s, const char *suffix) {
    if (!s || !suffix) {
        return 0;
    }

    size_t suffix_len = strlen(suffix);
    if (suffix_len > s->length) {
        return 0;
    }
    return strncmp(s->data + s->length - suffix_len, suffix, suffix_len) == 0;
}

/**
 * Compares two String objects lexicographically up to the length of the longest string.
 *
 * @param s1 Pointer to the first String object to compare.
 * @param s2 Pointer to the second String object to compare.
 *
 * @return A negative value if the first string is lexicographically less than the second,
 *         a positive value if the first string is lexicographically greater than the second,
 *         or zero if the strings are equal up to the length of the longest string.
 */
int string_compare(String *s1, String *s2) {
    size_t len1 = s1->length;
    size_t len2 = s2->length;
    size_t n = (len1 > len2) ? len1 : len2;
    return strncmp(s1->data, s2->data, n);
}

/**
 * Removes all leading and trailing whitespace characters from the String.
 *
 * @param s the String to modify
 */
void string_trimspace(String *s) {
    if (s->length == 0) {
        return;
    }

    int start = 0, end = s->length - 1;
    while (isspace(s->data[start]) && start < end) {
        start++;
    }
    while (isspace(s->data[end]) && end >= start) {
        end--;
    }

    if (start > 0 || end < (int)s->length - 1) {
        memmove(s->data, s->data + start, end - start + 1);
        s->length = (size_t)(end - start + 1);
        s->data[s->length] = '\0';
    }
}

/**
 * Removes all leading and trailing occurrences of the specified character from the String.
 * It does not remove characters in middle of string.
 *
 * @param s the String to modify
 * @param c the character to remove
 */
void string_trim(String *s, char c) {
    if (s->length == 0) {
        return;
    }

    int start = 0, end = s->length - 1;
    while (s->data[start] == c && start < end) {
        start++;
    }
    while (s->data[end] == c && end >= start) {
        end--;
    }

    if (start > 0 || end < (int)s->length - 1) {
        memmove(s->data, s->data + start, end - start + 1);
        s->length = end - start + 1;
        s->data[s->length] = '\0';
    }
}

/**Check if a pattern matches the String.
 * It returns 1 if there is a match and 0 otherwise. If there is an error in compiling the regular expression, it returns a non-zero error code.
 */
int string_regex_match(String *s, const char *pattern) {
    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return ret;
    }

    ret = regexec(&regex, s->data, 0, NULL, 0);
    regfree(&regex);

    if (ret != 0) {
        return 0;
    }
    return 1;
}

// Replace all occurrences of a pattern with a new string
// It returns 0 on success and a non-zero error code if an error occurs or
// regex can not be compiled.
int string_regex_replace(String *s, const char *pattern, const char *replacement) {
    regex_t regex;
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return ret;
    }

    size_t max_size = s->size;
    char *new_data = (char *)malloc(max_size);
    if (new_data == NULL) {
        regfree(&regex);
        return -1;
    }

    char *start = s->data;
    char *end = s->data + s->length;
    char *new_start = new_data;
    while (start < end) {
        regmatch_t match;
        ret = regexec(&regex, start, 1, &match, 0);
        if (ret == 0) {
            // Copy everything up to the start of the match
            size_t prefix_len = match.rm_so;
            memcpy(new_start, start, prefix_len);
            new_start += prefix_len;

            // Copy the replacement string
            size_t replacement_len = strlen(replacement);
            if (new_start + replacement_len >= new_data + max_size) {
                max_size *= 2;
                size_t offset = new_start - new_data;
                new_data = (char *)realloc(new_data, max_size);
                if (new_data == NULL) {
                    regfree(&regex);
                    free(new_data);
                    return -1;
                }
                new_start = new_data + offset;
            }
            memcpy(new_start, replacement, replacement_len);
            new_start += replacement_len;

            // Advance the pointer past the matched substring
            start += match.rm_eo;
        } else {
            // No match, copy the rest of the string
            size_t remaining_len = end - start;
            memcpy(new_start, start, remaining_len);
            new_start += remaining_len;
            break;
        }
    }

    // Null-terminate the new string and update the String object
    *new_start = '\0';
    size_t new_len = new_start - new_data;
    string_resize(s, new_len);
    memcpy(s->data, new_data, new_len);

    s->data[new_len] = '\0';  // NOLINT

    // Free the temporary buffer and clean up the regex object
    free(new_data);
    regfree(&regex);

    return 0;
}

void string_assign_cstr(String *s, const char *str) {
    size_t str_len = strlen(str);
    if (s->size < str_len + 1) {
        string_resize(s, str_len + 1);
    }
    strncpy(s->data, str, s->size);
    s->length = str_len;
}
