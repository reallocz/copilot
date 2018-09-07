#include "view.h"
#include <assert.h>
#include <stdio.h>
#include "../string.h"


void v_init(void* view, enum ViewType type)
{
    assert(view);

    // init common
    struct view* v = (struct view*) view;
    v->type        = type;
    v->width       = 0;
    v->height      = 0;
    stl_init(&v->stl);

    if (type == TEXTVIEW) {
        struct textview* tv = (struct textview*) view;
        tv->str             = str_empty();
    } else if (type == IMAGEVIEW) {
        struct imageview* iv = (struct imageview*) view;
        iv->path             = str_empty();
    } else if (type == STACKVG) {
        struct stackvg* sv = (struct stackvg*) view;
        sv->children       = NULL;
        sv->child_count    = 0;
    }
}


void v_debug(const struct view* v)
{
    printf("view (width: %d, height: %d, type: %s)\n", v->width, v->height,
           SViewType[v->type]);
}
