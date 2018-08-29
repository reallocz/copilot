#include "string.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PDEF_STRSIZE 16

/** Helper to set last char in data to '\0' */
static void str_terminate(struct string* str) {
    str->data[str->len - 1] = '\0';
}

struct string str_new(int size)
{
    struct string str;
    str.len  = size > 0 ? size + 1 : PDEF_STRSIZE;    // +1 for '\0'
    str.data = malloc(str.len * sizeof(char));
    return str;
}

void str_free(struct string* str)
{
    free(str->data);
    str->len = 0;
}


// Copy data over to string
void str_set(struct string* str, char* data)
{
    assert(data != NULL);
    int dlen = strlen(data);
    // Delete old data and allocate fresh memory
    str_free(str);
    str->len = dlen + 1;
    str->data = malloc(str->len * sizeof(char));
    assert(str->data != NULL);
    for (int i = 0; i < dlen; ++i) { str->data[i] = data[i]; }
    str_terminate(str);
}

void str_print(struct string* str)
{
    printf("string(len: %d, data[", str->len);
    for (int i = 0; i < str->len; ++i) { putchar(str->data[i]); }
    printf("])\n");
}
