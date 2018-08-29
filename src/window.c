#include "window.h"

#define PDEF_TITLE "Untitled Window"
#define PDEF_FONT "font.ttf"

struct window* win_new(unsigned int width, unsigned int height)
{
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


void win_update(struct window* win)
{
    // Clear screen in black
    SDL_SetRenderDrawColor(win->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(win->sdl_renderer);

    // !! Drawing start !!

    if (win->deck != NULL) {
        // Draw slide
        const struct deck* deck   = win->deck;
        const struct slide* slide = &deck->slides[deck->pointer];
        const struct color c      = slide->color;

        // Paint bg
        SDL_SetRenderDrawColor(win->sdl_renderer, c.r, c.g, c.b, c.a);
        SDL_RenderClear(win->sdl_renderer);

        // Render text
        SDL_Color scol;
        scol.r = 255;
        scol.g = 255;
        scol.b = 255;
        scol.a = 255;
        printf("Rendering: %s\n", slide->text.data);
        SDL_Surface* surf = TTF_RenderText_Solid(win->font, slide->text.data, scol);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(win->sdl_renderer, surf);

        SDL_Rect rect;
        rect.h = surf->h;
        rect.w = surf->w;
        rect.x = 0;
        rect.y =0;

        SDL_RenderCopy(win->sdl_renderer, tex, NULL, &rect);

        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);
    }


    // !! Drawing end !!

    // Update!
    SDL_RenderPresent(win->sdl_renderer);
    SDL_Delay(200);    // TODO remove!
}
