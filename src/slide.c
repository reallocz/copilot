#include "slide.h"
#include <assert.h>
#include <stdio.h>

void debug_deck(struct deck* deck)
{
    assert(deck != NULL);
    printf("deck (slide_count: %d, pointer: %d)\n", deck->slide_count, deck->pointer);
}

void debug_slide(struct slide* slide)
{
    assert(slide != NULL);
    // TODO
}
