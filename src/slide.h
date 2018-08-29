#pragma once
#include "string.h"
#include "style.h"

/** A deck is a collection on slides */
struct deck {
    struct slide* slides;
    int slide_count;      // total number of slides in deck
    int pointer;    // Points to current slide
};

struct slide {
    int init;    // -1 = uninitialized
    struct string text;
    struct color color;
};

void debug_deck(struct deck* deck);
void debug_slide(struct slide* slide);

