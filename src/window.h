#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "string.h"
#include "slide.h"

struct window {
    int quit;    // 1 = quit, 0 = don't
    // Dimensions and title
    unsigned int width, height;
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
 * NOTE: call window_start to actually initialize sdl and open up
 * a window.
 */
struct window* win_new(unsigned int width, unsigned int height);

void win_destroy(struct window* win);

// Open up the window
int win_start(struct window* win);

// Set up a deck to persent
void win_set_deck(struct window* win, struct deck* deck);

// Update every frame
void win_update(struct window* win);

