#include "style.h"
#include <stdio.h>

void stl_init(struct style* stl)
{
    stl->fgcol = COLWHITE;
    stl->bgcol = COLWHITE;
    stl->padding = (struct nrect){0, 0, 0, 0};
    stl->margin = (struct nrect){0, 0, 0, 0};
}
