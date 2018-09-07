#pragma once
#include "rect.h"

#define COL(r, g, b, a) \
    (struct color) { r, g, b, a }

#define SCOL(r, g, b, a) \
    (SDL_Color) { r, g, b, a }

#define TOSCOL(x) \
    (SDL_Color) { x.r, x.g, x.b, x.a }

#define COLWHITE \
    (struct color) { .r = 255, .g = 255, .b = 255, .a = 255 }
#define COLBLACK \
    (struct color) { 0, 0, 0, 255 }
#define COLRED \
    (struct color) { 255, 0, 0, 255 }
#define COLGREEN \
    (struct color) { 0, 0, 0, 255 }
#define COLBLUE \
    (struct color) { 0, 0, 255, 255 }


/** style.h contains all possible slide styling options */


/** 256 bit color values */
struct color {
    unsigned char r, g, b, a;    // 0-255
};


/** view styling options */
struct style {
    struct color fgcol, bgcol;
    struct nrect padding;
    struct nrect margin;
};


void stl_init(struct style* stl);
