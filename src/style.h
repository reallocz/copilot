#pragma once
#include <SDL2/SDL_ttf.h>

/** style.h contains all possible slide styling options */


/** 256 bit color values */
struct color {
    unsigned char r, g, b, a;   // 0-255
};


/** Meta information about fonts */
struct font {
    int flags;
    TTF_Font* ttf_font; // SDL_Ttf font pointer
    int ptsize;
};

