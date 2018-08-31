#include <stdio.h>
#include "flags.h"
#include "string.h"
#include "style.h"

struct font font_load(struct string* path, int ptsize)
{
    assert(path != NULL);
    assert(ptsize > 0);
    struct font ft = {0};
    ft.flags = 0;
    ft.ptsize      = ptsize;
    ft.ttf_font    = TTF_OpenFont(path->data, ft.ptsize);
    if (ft.ttf_font == NULL) {
        printf("Failed to open font '%s': %s\n", path->data, TTF_GetError());
        return ft;
    }

    FSET(ft, FINIT);
    return ft;
}

void font_close(struct font* font)
{
    assert(font);
    TTF_CloseFont(font->ttf_font);
    FUSET((*font), FINIT);
    FSET((*font), FCLOSED);
}
