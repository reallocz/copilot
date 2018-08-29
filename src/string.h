#pragma once

/**
 * A null terminated string wrapper
 * All standard <string.h> functions should work on 'string.data'.
 */
struct string {
    char* data;
    int len;    // Fixed length excluding '\0'
};

/**
 * Returns a mutable string of 'size' bytes.
 * If size is 0, size is set to default size.
 */
struct string str_new(int size);

/** Free string */
void str_free(struct string* str);

/** Set value to string */
void str_set(struct string* str, char* data);

/** Debug string */
void str_print(struct string* str);

