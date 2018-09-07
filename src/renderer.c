#include "renderer.h"
#include <assert.h>
#include <stdio.h>
#include "view/rect.h"


struct renderer {
    SDL_Renderer* sdl_renderer;
    TTF_Font* font;
    struct color color;

    // Drawing bounds
    struct rect bounds;
};

static struct renderer R;

void r_init(SDL_Renderer* sdl_renderer)
{
    assert(sdl_renderer);
    R.sdl_renderer = sdl_renderer;

    // TODO should this be kept as default?
    SDL_SetRenderDrawBlendMode(R.sdl_renderer, SDL_BLENDMODE_BLEND);
}

/** Only used by window! */
void _r_render()
{
    SDL_RenderPresent(R.sdl_renderer);
}

void r_clearscreen()
{
    SDL_SetRenderDrawColor(R.sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(R.sdl_renderer);
}

void r_clear()
{
    SDL_SetRenderDrawColor(R.sdl_renderer, R.color.r, R.color.g, R.color.b,
                           R.color.a);
    SDL_RenderClear(R.sdl_renderer);
}

void r_setfont(TTF_Font* font)
{
    assert(font);
    R.font = font;
}

void r_setcolor(struct color c)
{
    R.color = c;
    SDL_SetRenderDrawColor(R.sdl_renderer, c.r, c.g, c.b, c.a);
}

void r_setbounds(struct rect bounds)
{
    R.bounds = bounds;
}

void r_drawtext(const char* text, const struct style* stl)
{
    /*assert(text);*/
    SDL_Surface* surf;
    SDL_Texture* texture;

    // create rendered font surface and texture
    SDL_Color txtcol;
    if (stl == NULL) {
        txtcol = TOSCOL(R.color);
    } else {
        struct color c = stl->fgcol;
        txtcol         = (SDL_Color){c.r, c.g, c.b, c.a};
    }
    surf = TTF_RenderText_Solid(R.font, text, txtcol);
    assert(surf);
    texture = SDL_CreateTextureFromSurface(R.sdl_renderer, surf);
    assert(texture);

    // calculate layout
    int fwidth = 0, fheight = 0;
    float aspect = 1. * surf->w / surf->h;
    if (surf->h > R.bounds.h) {
        fheight = R.bounds.h;
        fwidth  = aspect * fheight;
    } else if (surf->w > R.bounds.w) {
        fwidth  = R.bounds.w;
        fheight = fwidth / aspect;
    } else {
        fheight = surf->h;
        fwidth  = surf->w;
    }
    /*printf("Aspect: %f, fwidth: %d, fheight: %d\n", aspect, fwidth, fheight);*/
    SDL_Rect r = {R.bounds.x, R.bounds.y, fwidth, fheight};


    // Render texture and free resources
    SDL_RenderCopy(R.sdl_renderer, texture, NULL, &r);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
    (void) stl;
}


void r_drawrect(struct rect r)
{
    SDL_Rect rect = (SDL_Rect){.x = r.x, .y = r.y, .w = r.w, .h = r.h};
    SDL_RenderFillRect(R.sdl_renderer, &rect);
}

// Forward declerations
static void drawtextview(struct textview*);
static void drawimageview(struct imageview*);
static void drawstackvg(struct stackvg*);

void r_drawview(void* view)
{
    assert(view);
    struct view* v = (struct view*) view;
    if (v->type == EMPTY) {
        // TODO draw empty rect
    } else if (v->type == TEXTVIEW) {
        drawtextview((struct textview*) view);
    } else if (v->type == IMAGEVIEW) {
        drawimageview((struct imageview*) view);
    } else if (v->type == STACKVG) {
        drawstackvg((struct stackvg*) view);
    }
}


static void drawtextview(struct textview* tv)
{
    /*printf("Drawing textview...\n");*/
    r_drawtext(tv->str.data, &tv->v.stl);
}
static void drawimageview(struct imageview* iv)
{
    printf("Drawing imageview\n");
}
static void drawstackvg(struct stackvg* svg)
{
    printf("Drawing stackvg\n");
}
