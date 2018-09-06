#pragma once

/**
 * A null terminated string wrapper
 * All standard <string.h> functions should work on 'string.data'.
 */
struct string {
    char* data;
    int len;    // Fixed length excluding '\0'
};

/** Returns unallocated empty string */
struct string str_empty(void);


/** Free string */
void str_free(struct string* str);


/** Create a new string from data. */
struct string str_from(const char* data);


/** Deletes current string and creates a new one from data */
void str_set(struct string* str, const char* data);

/** Debug string */
void str_debug(const struct string* str);
