#include "../include/str.h"

#include <assert.h>
#include <stdio.h>

void test_string_init() {
    String *s = string_init();
    assert(s != NULL);
    assert(string_data(s) != NULL);
    assert(string_length(s) == 0);
    string_free(s);
}

void test_string_new() {
    String *s = string_new("Hello World");
    assert(s != NULL);
    assert(string_data(s) != NULL);
    assert(string_length(s) == 11);
    string_free(s);
}

void test_string_resize() {
    String *s = string_init();
    string_resize(s, 10);
    string_free(s);
}

void test_string_append() {
    String *s = string_init();
    string_append_cstr(s, "Hello, ");
    string_append_cstr(s, "world!");
    assert(string_length(s) == 13);
    assert(strcmp(string_data(s), "Hello, world!") == 0);
    string_free(s);
}

void test_string_append_len() {
    String *s = string_init();
    string_resize(s, 20);
    string_append_len(s, "Hello, world!", 5);
    assert(strcmp(string_data(s), "Hello") == 0);
    string_free(s);
}

void test_string_insert() {
    // Test inserting at index 0
    String *s = string_new("bcd");
    string_insert(s, "a", 0);
    string_insert(s, "e", 3);
    string_insert(s, "f", 4);

    assert(strcmp(string_data(s), "abcefd") == 0);
    string_free(s);

    // Test inserting at the end of the string
    s = string_new("abc");
    string_insert(s, "def", 3);
    assert(strcmp(string_data(s), "abcdef") == 0);
    string_free(s);

    // Test inserting in the middle of the string
    s = string_new("abcdefgh");
    string_insert(s, "12345", 3);
    assert(strcmp(string_data(s), "abc12345defgh") == 0);
    string_free(s);
}

void test_string_remove() {
    String *s = string_new("Hello, world!");
    string_remove(s, 7, 5);
    assert(strcmp(string_data(s), "Hello, !") == 0);
    string_free(s);
}

void test_string_replace() {
    String *s = string_new("Hello, world!");
    string_replace(s, 7, 5, "there");
    assert(strcmp(string_data(s), "Hello, there!") == 0);
    string_free(s);
}

void test_string_replace_all() {
    String *s = string_new("one, two, three, four");
    String *new_str = string_replace_all(s, "o", "0");
    assert(strcmp(string_data(new_str), "0ne, tw0, three, f0ur") == 0);
    string_free(new_str);
    string_free(s);
}

void test_string_char_at() {
    String *s = string_new("Hello");
    assert(string_char_at(s, 1) == 'e');
    string_free(s);
}

void test_string_index_of() {
    String *s = string_new("Hello, world!");
    assert(string_index_of(s, "world", 0) == 7);
    assert(string_index_of(s, "l", 3) == 3);
    assert(string_index_of(s, "nope", 0) == -1);
    string_free(s);
}

void test_string_split() {
    String *s = string_new("one,two,three,four");

    int count;
    char **substrings = string_split(s, ',', &count);
    assert(count == 4);
    assert(strcmp(substrings[0], "one") == 0);
    assert(strcmp(substrings[1], "two") == 0);
    assert(strcmp(substrings[2], "three") == 0);
    assert(strcmp(substrings[3], "four") == 0);
    free(substrings);
    string_free(s);
}

void test_string_split_n() {
    String *s = string_new("hello,world,test");

    int count;
    char **parts = string_split_n(s, ',', 2, &count);

    assert(count == 2);
    assert(strcmp(parts[0], "hello") == 0);
    assert(strcmp(parts[1], "world,test") == 0);

    // Clean up
    for (int i = 0; i < count; i++) {
        free(parts[i]);
    }

    free(parts);
    string_free(s);
}

void test_string_length() {
    String *str = string_new("Hello World");
    assert(string_length(str) == 11);
}

void test_string_clone() {
    String *str = string_new("Hello World");
    String *clone = string_clone(str);
    assert(string_compare(clone, str) == 0);
}

void test_string_concatenate() {
    String *str1 = string_new("Hello");
    String *str2 = string_new(" World");
    string_append(str1, str2);
    assert(string_compare(str1, string_new("Hello World")) == 0);
}

void test_string_compare() {
    String *str1 = string_new("abc");
    String *str2 = string_new("def");
    assert(string_compare(str1, str2) < 0);

    String *str3 = string_new("hello");
    String *str4 = string_new("HELLO");
    assert(string_compare(str3, str4) > 0);

    String *str5 = string_new("cat");
    String *str6 = string_new("cat");
    assert(string_compare(str5, str6) == 0);
}

// Test for string_trimspace function
void test_string_trimspace() {
    String *s1 = string_new("   hello  ");
    String *s2 = string_new("hello");
    String *s3 = string_new("  hello   world  ");
    String *s4 = string_new("hello   world");

    string_trimspace(s1);
    string_trimspace(s2);
    string_trimspace(s3);
    string_trimspace(s4);

    assert(string_compare(s1, s2) == 0);
    assert(string_compare(s3, string_new("hello   world")) == 0);
    assert(string_compare(s4, string_new("hello   world")) == 0);

    string_free(s1);
    string_free(s2);
    string_free(s3);
    string_free(s4);
}

// Test for string_trim function
void test_string_trim() {
    String *s1 = string_new("hello");
    String *s2 = string_new("hello   ");
    String *s3 = string_new("   hello");
    String *s4 = string_new("   hello   ");
    String *s5 = string_new("llhello worldll");
    String *s6 = string_new("zzhello world");

    string_trim(s1, 'h');
    string_trim(s2, ' ');
    string_trim(s3, ' ');
    string_trim(s4, ' ');
    string_trim(s5, 'l');
    string_trim(s6, 'z');

    assert(string_compare(s1, string_new("ello")) == 0);
    assert(string_compare(s2, string_new("hello")) == 0);
    assert(string_compare(s3, string_new("hello")) == 0);
    assert(string_compare(s4, string_new("hello")) == 0);
    assert(string_compare(s5, string_new("hello world")) == 0);
    assert(string_compare(s6, string_new("hello world")) == 0);

    string_free(s1);
    string_free(s2);
    string_free(s3);
    string_free(s4);
    string_free(s5);
    string_free(s6);
}

void test_string_regex_match() {
    String *s = string_new("Hello, world!");
    const char *pat = "Hello";

    assert(string_regex_match(s, pat) == 1);
    string_free(s);
}

void test_string_regex_replace() {
    String *s = string_new("The quick brown fox jumps over the lazy dog.");
    const char *pat = "quick\\s+brown";
    string_regex_replace(s, pat, "fast and brown");
    assert(strcmp(string_data(s), "The fast and brown fox jumps over the lazy dog.") == 0);
    string_free(s);
}

void test_string_assign_cstr() {
    String *s = string_new("The quick brown fox jumps over the lazy dog.");
    string_assign_cstr(s, "Hello World");
    assert(strcmp(string_data(s), "Hello World") == 0);
}

int main() {
    test_string_new();
    test_string_resize();
    test_string_append();
    test_string_append_len();
    test_string_insert();
    test_string_remove();
    test_string_replace();
    test_string_replace_all();

    test_string_char_at();
    test_string_index_of();
    test_string_split();
    test_string_split_n();
    test_string_length();
    test_string_clone();
    test_string_concatenate();
    test_string_compare();
    test_string_compare();
    test_string_trimspace();
    test_string_trim();

    test_string_regex_match();
    test_string_regex_replace();
    test_string_assign_cstr();
    printf("All Tests passed!\n");
    return 0;
}
