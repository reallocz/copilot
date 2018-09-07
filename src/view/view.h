#pragma once
#include "../string.h"
#include "style.h"


enum ViewType { EMPTY = 0, TEXTVIEW, IMAGEVIEW, STACKVG };

static const char* SViewType[] = {"empty", "textview", "imageview", "stackvg"};


#define VTYPE(x) (struct view*) x->type

/**
 * Base struct which describes a view
 * This is included in all types of views as 'v'
 */
struct view {
    enum ViewType type;
    int width, height;
    struct style stl;
};

/** Views */

struct textview {
    struct view v;
    struct string str;
};

struct imageview {
    struct view v;
    struct string path;
};

/** Viewgroups */

struct stackvg {
    struct view v;
    void* children;
    int child_count;
};


/** Initialize all kinds of views to default values */
void v_init(void* view, enum ViewType);

void v_debug(const struct view* v);
