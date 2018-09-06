#include "window.h"
#include <assert.h>

#define PDEF_TITLE "Untitled Window"
#define PDEF_FONT "font.ttf"

// Easy indexing for surf, texture and rect arrays
enum { SLIDE = 0, SLIDENO, TOTAL };

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
    win->title = str_from(PDEF_TITLE);
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


static int _init_sdl(struct window* win)
{
    int err;
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

    printf("sdl initialized successfully!\n");
    return 0;
}

static int _init_ttf(struct window* win)
{
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
    return 0;
}

int win_show(struct window* win)
{
    int err = 0;
    err     = _init_sdl(win);
    err     = _init_ttf(win);
    return err;
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
    const int scrwidth  = win->width;
    const int scrheight = win->height;

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
        SDL_Color txtcol = {255, 255, 255, 255};    // White

        surfs[SLIDE] =
            TTF_RenderText_Solid(win->font, slide->text.data, txtcol);
        textures[SLIDE] =
            SDL_CreateTextureFromSurface(win->sdl_renderer, surfs[SLIDE]);

        // Calculate text location(currently at the middle of the screen)
        SDL_Rect* r = &rects[SLIDE];
        r->h        = surfs[SLIDE]->h;
        r->w        = surfs[SLIDE]->w;
        r->x        = (scrwidth - r->w) / 2;
        r->y        = (scrheight - r->h) / 2;
    }

    // Draw slide number at centre of bottom edge.
    {

        SDL_Color txtcol = {255, 255, 255, 255};    // White

        char* format = "%d-%d";                  // Slide '02/24'
        char buffer[7];                          // Max 7 chars '999/999'
        int slideno = win->deck->pointer + 1;    // 1 indexed
        snprintf(buffer, 7, format, slideno, win->deck->slide_count);
        surfs[SLIDENO] = TTF_RenderText_Solid(win->font, buffer, txtcol);
        textures[SLIDENO] =
            SDL_CreateTextureFromSurface(win->sdl_renderer, surfs[SLIDENO]);



        // Claculate text location (100px * 50px)
        SDL_Rect* r = &rects[SLIDENO];
        r->h        = surfs[SLIDENO]->h / 3;    // Currently scaled down by 3
        r->w        = surfs[SLIDENO]->w / 3;
        r->x        = (scrwidth - r->w) / 2;
        r->y        = (scrheight - r->h) - 5;    // 5 padding at the bottom
    }



    // !! Drawing end !!


    // Render copy to the screen
    {
        // render slide text
        SDL_RenderCopy(win->sdl_renderer, textures[SLIDE], NULL, &rects[SLIDE]);

        // render slide number bg box
        SDL_SetRenderDrawColor(win->sdl_renderer, 0, 0, 0, 100);
        SDL_Rect snr;
        int xpadding = 6, ypadding = 1;
        snr.w = rects[SLIDENO].w + xpadding * 2;
        snr.h = rects[SLIDENO].h + ypadding * 2;
        snr.x = rects[SLIDENO].x - (xpadding);
        snr.y = rects[SLIDENO].y - (ypadding);
        SDL_SetRenderDrawBlendMode(win->sdl_renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(win->sdl_renderer, &snr);
        SDL_SetRenderDrawBlendMode(win->sdl_renderer, SDL_BLENDMODE_NONE);
        // render slide no
        SDL_RenderCopy(win->sdl_renderer, textures[SLIDENO], NULL,
                       &rects[SLIDENO]);
    }

    // Free all created textures and surfaces
    {
        SDL_FreeSurface(surfs[SLIDE]);
        SDL_FreeSurface(surfs[SLIDENO]);
        SDL_DestroyTexture(textures[SLIDE]);
        SDL_DestroyTexture(textures[SLIDENO]);
    }

    // Update!
    SDL_RenderPresent(win->sdl_renderer);
}
