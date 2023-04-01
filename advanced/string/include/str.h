#ifndef __STR_H__
#define __STR_H__

#include <regex.h>
#include <stdlib.h>
#include <string.h>

/**
 * The string struct represents a dynamic string.
 * It consists of a character array, the size of the array, and the length of the string.
 */
typedef struct String String;

/**
 * Allocates memory for a new String structure and initializes it with the provided null-terminated string.
 *
 * @param str The null-terminated string to initialize the new String structure with. If NULL is passed, an empty string is created.
 * @return The new String structure that has been allocated and initialized with the provided string, or an empty string if str is NULL.
 * @remark It is the responsibility of the caller to free the memory of the returned structure using string_free().
 */
String *string_new(const char *str);

/**
 * Allocates memory for a new String object.
 *
 * @return A pointer to the new String object, or NULL if memory allocation fails.
 */
String *string_init();

/**
 * Frees the memory allocated for a String object.
 *
 * @param s A pointer to the String object to be freed.
 */
void string_free(String *s);

/**
 * frees the memory allocated for the substrings obtained from the string_split
 * functions.
 */
void string_free_substrings(char **arr, int count);

/**
 * Resizes the character array of a String object.
 *
 * @param s A pointer to the String object to be resized.
 * @param new_size The new size of the character array.
 */
void string_resize(String *s, size_t new_size);

/**
 * Appends a string to the end of a String object.
 *
 * @param src A pointer to the source String object that will be modified.
 * @param str A pointer to the String object to append to src.
 */
void string_append(String *src, String *str);

/**
 * Appends a string to the end of a String object.
 *
 * @param src A pointer to the source String object that will be modified.
 * @param str A character pointer.
 */
void string_append_cstr(String *src, const char *str);

/**
 * Appends a specified number of characters to the end of a String object.
 *
 * @param s A pointer to the String object.
 * @param data A pointer to the string to append.
 * @param len The number of characters to append.
 * @return 1 if successful, 0 otherwise.
 */
int string_append_len(String *s, const char *data, int len);

/**
 * Inserts a string into a String object at a specified index.
 *
 * @param s A pointer to the String object.
 * @param str The string to be inserted.
 * @param index The index at which to insert the string.
 */
void string_insert(String *s, const char *str, size_t index);

/**
 * Removes a portion of a string from a String object.
 *
 * @param s A pointer to the String object.
 * @param index The starting index of the portion to be removed.
 * @param count The number of characters to remove.
 */
void string_remove(String *s, size_t index, size_t count);

/**
Replaces a portion of a string in a String object with a new string.
@param s A pointer to the String object.
@param index The starting index of the portion to be replaced.
@param count The number of characters to replace.
@param new_str The string to replace the portion with.
*/
void string_replace(String *s, size_t index, size_t count, const char *new_str);

/**
Replaces all occurrences of a substring in a String object with another substring.
@param s A pointer to the String object.
@param old_substr The substring to replace.
@param new_substr The substring to replace with.
@return A pointer to a new String object that contains the modified string.
*/
String *string_replace_all(String *s, const char *old_substr, const char *new_substr);

/**
Returns the character at a specified index in a String object.
@param s A pointer to the String object.
@param index The index of the desired character.
@return The character at the specified index.
*/
char string_char_at(String *s, size_t index);

/**
 * Returns the index of the first occurrence of a substring in a String object,
 * starting from a specified position. Returns -1 if the substring is not found.
 *
 * @param s A pointer to the String object.
 * @param substr The substring to search for.
 * @param start_index The starting position of the search.
 * @return The index of the first occurrence of the substring, or -1 if not found.
 */
int string_index_of(String *s, const char *substr, int start_index);

// Set a new string from a c string.
void string_assign_cstr(String *s, const char *str);

/**
Returns a pointer to the character array of a String object.
@param s A pointer to the String object.
@return A pointer to the character array.
*/
char *string_data(String *s);

/**
Returns the length of a String object.
@param s A pointer to the String object.
@return The length of the string.
*/
size_t string_length(String *s);

/**
 * Splits a String object into an array of substrings based on a delimiter character.
 *
 * @param s A pointer to the String object.
 * @param delimiter The delimiter character to split the string with.
 * @param count A pointer to an integer to store the number of substrings in the resulting array.
 * @return An array of pointers to the resulting substrings.
 */
char **string_split(String *s, char delimiter, int *count);

/**
 * Splits a String object into an array of substrings based on a delimiter character, up to a maximum number of substrings.
 *
 * @param s A pointer to the String object.
 * @param delimiter The delimiter character to split the string with.
 * @param max_count The maximum number of substrings to include in the resulting array.
 * @param count A pointer to an integer to store the actual number of substrings in the resulting array.
 * @return An array of pointers to the resulting substrings.
 */
char **string_split_n(String *s, char delimiter, int max_count, int *count);

/**
Joins an array of substrings into a new String object, separated by a delimiter character.

@param substrings An array of pointers to the substrings to join.
@param count The number of substrings in the array.
@param delimiter The delimiter character to separate the substrings with.
@return A pointer to a new String object that contains the joined substrings.
*/
String *string_join(char **substrings, int count, char delimiter);

/**

Returns a substring of a String object starting at a specified index and ending at a specified index.

@param s A pointer to the String object.
@param start The starting index of the substring.
@param end The ending index of the substring.
@return A pointer to a new String object that contains the specified substring.
*/
String *string_substring(String *s, size_t start, size_t end);

/**
Converts all lowercase characters in a String object to uppercase.
@param s A pointer to the String object.
@return A pointer to a new String object that contains the converted string.
*/
String *string_to_upper(String *s);

/**
Converts all uppercase characters in a String object to lowercase.
@param s A pointer to the String object.
@return A pointer to a new String object that contains the converted string.
*/
String *string_to_lower(String *s);

/**
 * Reverses the characters in a String object in place.
 * It has a time complexity of O(n/2) and a space complexity of O(1).
 * @param s A pointer to the String object.
 */
void string_reverse(String *s);

/**
 * Creates a new String object that is a copy of an existing String object.
 *
 * @param s A pointer to the String object to clone.
 * @return A pointer to the new String object, or NULL if memory allocation fails.
 */
String *string_clone(String *s);

/**
 * Checks if a String object starts with a specified prefix.
 *
 * @param s A pointer to the String object.
 * @param prefix A pointer to the prefix string.
 * @return 1 if the String object starts with the prefix, or 0 otherwise.
 */
int string_startswith(String *s, const char *prefix);

/**
 * Checks if a String object ends with a specified suffix.
 *
 * @param s A pointer to the String object.
 * @param suffix A pointer to the suffix string.
 * @return 1 if the String object ends with the suffix, or 0 otherwise.
 */
int string_endswith(String *s, const char *suffix);

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
int string_compare(String *s1, String *s2);

/**
 * Removes all leading and trailing whitespace characters from the String.
 *
 * @param s the String to modify
 */
void string_trimspace(String *s);

/**
 * Removes all leading and trailing occurrences of the specified character from the String.
 *
 * @param s the String to modify
 * @param c the character to remove
 */
void string_trim(String *s, char c);

/**Check if a pattern matches the String.
 * It returns 1 if there is a match and 0 otherwise. If there is an error in compiling the regular expression, it returns a non-zero error code.
 */
int string_regex_match(String *s, const char *pattern);

// Replace all occurrences of a pattern with a new string
// It returns 0 on success and a non-zero error code if an error occurs or
// regex can not be compiled.
int string_regex_replace(String *s, const char *pattern, const char *replacement);

#endif /* __STR_H__ */
