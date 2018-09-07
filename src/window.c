#include "window.h"
#include <assert.h>
#include "renderer.h"
#include "view/style.h"

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
    r_init(win->sdl_renderer);
    r_setfont(win->font);
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

    r_clearscreen();

    {    // Draw slide
        r_setbounds((struct rect){0, 0, scrwidth, scrheight / 3});
        const struct slide* slide = &win->deck->slides[win->deck->pointer];
        // Paint bg
        struct view* v = (struct view*) slide->view;
        r_setcolor(COLWHITE);
        r_clear();
        // Draw slide contents
        r_drawview(slide->view);
    }



    // Draw slide number at centre of bottom edge.
    {

        char* format = "%d-%d";    // Slide '02/24'
        char buffer[7];            // Max 7 chars '999/999'

        int slideno = win->deck->pointer + 1;    // 1 indexed
        snprintf(buffer, 7, format, slideno, win->deck->slide_count);

        struct textview tv;
        v_init(&tv, TEXTVIEW);
        tv.str         = str_from(buffer);
        tv.v.stl.fgcol = COL(0, 0, 0, 255);

        struct rect bnd;
        bnd.h = scrheight / 10;
        bnd.w = scrwidth / 10;
        bnd.y = scrheight - bnd.h;
        bnd.x = (scrwidth - bnd.w) / 2;

        r_setbounds(bnd);
        r_setcolor(COLRED);
        r_drawview(&tv);
    }


    // Update!
    _r_render();
}
