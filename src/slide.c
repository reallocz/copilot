#include "slide.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


struct deck dk_new(int slide_count)
{
    struct deck dk = {NULL, 0, 0};
    dk.slide_count = slide_count;
    dk.slides      = malloc(dk.slide_count * sizeof(struct slide));
    assert(dk.slides);
    return dk;
}


void dk_free(struct deck* dk)
{
    assert(dk);
    // TODO
}

void debug_deck(const struct deck* deck)
{
    assert(deck != NULL);
    printf("deck (slide_count: %d, pointer: %d)\n", deck->slide_count,
           deck->pointer);
}

void debug_slide(const struct slide* slide)
{
    assert(slide != NULL);
}
