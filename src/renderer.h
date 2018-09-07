#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "view/style.h"
#include "view/view.h"

/** Inititalize renderer with sdl_renderer */
void r_init(SDL_Renderer* sdl_renderer);
/** Render contents to screen. (only used by window) */
void _r_render();

/** Drawing props */

void r_setfont(TTF_Font* font);
void r_setcolor(struct color c);
void r_setbounds(struct rect bounds);

/** Clear screen to black */
void r_clearscreen();
/** Clear screen to set color */
void r_clear();

/** Draw all kinds of views */
void r_drawview(void* view);

/** drawing functions */
void r_drawtext(const char* text, const struct style* stl);
void r_drawrect(struct rect r);
