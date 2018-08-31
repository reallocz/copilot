#pragma once
#include "string.h"
#include "style.h"


/** Loads font from path for size */
struct font font_load(struct string* path, int ptsize);

void font_close(struct font* font);
