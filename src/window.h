#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "string.h"
#include "slide.h"

struct window {
    int quit;    // 1 = quit, 0 = don't

    int width, height;
    struct string title;

    struct deck* deck;

    // SDL stuff
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    // Font stuff
    TTF_Font* font;
};

/**
 * Create a new window with provided values
 * NOTE: call window_show to actually initialize sdl and open up
 * a window.
 */
struct window* win_new(unsigned int width, unsigned int height);

/** Cleanup sdl, ttf etc */
void win_destroy(struct window* win);

/** Init sdl, ttf and display the window */
int win_show(struct window* win);

/**
 * Updates window.width and window.height fields.
 * Returns 1 if size was updated
 */
int win_update_size(struct window* win);

// Render current contents
void win_render(const struct window* win);

