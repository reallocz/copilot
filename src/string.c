#include "string.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PDEF_STRSIZE 16

/** Helper to set last char in data to '\0' */
static void str_terminate(struct string* str)
{
    str->data[str->len] = '\0';    // data is len + 1 long so ok.
}


struct string str_empty(void)
{
    struct string str = {.data = NULL, .len = 0};
    return str;
}


void str_free(struct string* str)
{
    if (str->data == NULL) {
        printf("warning: double free string!\n");
        return;
    } else {
        free(str->data);
        str->data = NULL;
        str->len  = 0;
    }
}


struct string str_from(const char* data)
{
    assert(data != NULL);
    struct string str = {.data = NULL, .len = 0};
    int dlen          = strlen(data);
    str.len           = dlen;
    str.data =
        malloc((str.len + 1) * sizeof(char));    // +1 for null terminator
    assert(str.data != NULL);
    strcpy(str.data, data);
    str_terminate(&str);
    return str;
}


void str_set(struct string* str, const char* data)
{
    assert(str != NULL);
    assert(data != NULL);
    str_free(str);
    *str = str_from(data);
}


void str_debug(const struct string* str)
{
    printf("string(len: %d, data[", str->len);
    for (int i = 0; i < str->len; ++i) {
        putchar(str->data[i]);
    }
    printf("])\n");
}
