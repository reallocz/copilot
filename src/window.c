#include "window.h"

#define PDEF_TITLE "Untitled Window"

struct window* win_new(unsigned int width, unsigned int height)
{
    struct window* win = malloc(sizeof(struct window));
    win->quit          = 0;
    win->width         = width;
    win->height        = height;
    win->deck          = NULL;
    struct string title = str_new(0);
    str_set(&title, PDEF_TITLE);
    win->title         = title;
    return win;
}


void win_destroy(struct window* win)
{
    SDL_DestroyRenderer(win->sdl_renderer);
    SDL_DestroyWindow(win->sdl_window);
    SDL_Quit();
}


void win_set_deck(struct window* win, struct deck* deck)
{
    printf("slide deck set!\n");
    win->deck = deck;
}

int win_start(struct window* win)
{
    int err;
    // Init sdl
    err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS |
                   SDL_INIT_TIMER);
    if (err != 0) {
        printf("Error!!");
        SDL_Log("Unable to init sdl: %s", SDL_GetError());
        return 1;
    }

    // Create sdl_window
    win->sdl_window =
        SDL_CreateWindow(win->title.data, SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, win->width, win->height, 0);
    if (win->sdl_window == NULL) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 1;
    }

    // Create sdl_renderer
    win->sdl_renderer = SDL_CreateRenderer(win->sdl_window, -1, 0);
    if (win->sdl_renderer == NULL) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return 1;
    }

    printf("Display initialized successfully!\n");
    return 0;
}


void win_update(struct window* win)
{
    // Clear screen in black
    SDL_SetRenderDrawColor(win->sdl_renderer, 210, 0, 0, 55);
    SDL_RenderClear(win->sdl_renderer);

    // !! Drawing start !!

    if (win->deck != NULL) {
        // Draw slide
        const struct deck* deck = win->deck;
        const struct slide* slide = &deck->slides[deck->pointer];
        const struct color c = slide->color;
        SDL_SetRenderDrawColor(win->sdl_renderer, c.r, c.g, c.b, c.a);
        SDL_RenderClear(win->sdl_renderer);
    }


    // !! Drawing end !!

    // Update!
    SDL_RenderPresent(win->sdl_renderer);
    SDL_Delay(200);    // TODO remove!
}
