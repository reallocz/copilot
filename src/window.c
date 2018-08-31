#include "window.h"
#include <assert.h>

#define PDEF_TITLE "Untitled Window"
#define PDEF_FONT "font.ttf"

// Easy indexing for global textures and surfaces
enum { SLIDE = 0, SLIDENO, FPS, TOTAL };

struct window* win_new(unsigned int width, unsigned int height)
{
    assert(width > 0);
    assert(height > 0);

    struct window* win = malloc(sizeof(struct window));
    win->quit          = 0;
    win->width         = width;
    win->height        = height;
    win->deck          = NULL;
    win->sdl_window    = NULL;
    win->sdl_renderer  = NULL;
    win->font          = NULL;

    // Set title
    struct string title = str_new(0);
    str_set(&title, PDEF_TITLE);
    win->title = title;
    return win;
}


void win_destroy(struct window* win)
{
    TTF_CloseFont(win->font);
    TTF_Quit();
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
    {    // SDL init
        int err;
        err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS |
                       SDL_INIT_TIMER);
        if (err != 0) {
            printf("Error!!");
            SDL_Log("Unable to init sdl: %s", SDL_GetError());
            return 1;
        }

        // Create sdl_window
        win->sdl_window = SDL_CreateWindow(
            win->title.data, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            win->width, win->height, 0);
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
    }

    {    // SDL_ttf init
        if (TTF_Init() == -1) {
            printf("TTF_Init error: %s\n", TTF_GetError());
            return 1;
        }
        win->font = TTF_OpenFont(PDEF_FONT, 80);
        if (win->font == NULL) {
            printf("Failed to open font.ttf: %s\n", TTF_GetError());
            return 1;
        }
        printf("Font loaded successfully!\n");
    }
    return 0;
}

int win_update_size(struct window* win)
{
    int was_resized = 0;
    int newwidth, newheight;
    SDL_GetWindowSize(win->sdl_window, &newwidth, &newheight);

    // Update window fields if they have changed
    if (newwidth != win->width || newheight != win->height) {
        win->width  = newwidth;
        win->height = newheight;
        was_resized = 1;
    }

    return was_resized;
}


void win_render(const struct window* win)
{
    /*const int scrwidth  = win->width;*/
    /*const int scrheight = win->height;*/

    // Clear screen in black
    SDL_SetRenderDrawColor(win->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(win->sdl_renderer);

    // !! Drawing start !!
    SDL_Rect rects[TOTAL];
    SDL_Surface* surfs[TOTAL];
    SDL_Texture* textures[TOTAL];

    // Draw slide
    {
        /*printf("Rendering: %s\n", slide->text.data);*/

        const struct slide* slide = &win->deck->slides[win->deck->pointer];
        const struct color bgcol  = slide->color;

        // Paint bg
        SDL_SetRenderDrawColor(win->sdl_renderer, bgcol.r, bgcol.g, bgcol.b,
                               bgcol.a);
        SDL_RenderClear(win->sdl_renderer);

        // Render text
        SDL_Color txtcol = {255, 255, 255, 255};

        surfs[SLIDE] = TTF_RenderText_Solid(win->font, slide->text.data, txtcol);
        textures[SLIDE] = SDL_CreateTextureFromSurface(win->sdl_renderer, surfs[SLIDE]);

        rects[SLIDE].h = surfs[SLIDE]->h;
        rects[SLIDE].w = surfs[SLIDE]->w;
        rects[SLIDE].x = 0;
        rects[SLIDE].y = 0;
    }

    // !! Drawing end !!


    // Render copy on the screen
    SDL_RenderCopy(win->sdl_renderer, textures[SLIDE], NULL, &rects[SLIDE]);
    // Free all created textures and surfaces
    SDL_FreeSurface(surfs[SLIDE]);
    SDL_DestroyTexture(textures[SLIDE]);

    // Update!
    SDL_RenderPresent(win->sdl_renderer);
}
