#pragma once
#include "string.h"
#include "view/style.h"
#include "view/view.h"

/** A deck is a collection on slides */
struct deck {
    struct slide* slides;
    int slide_count;    // total number of slides in deck
    int pointer;        // Points to current slide
};

struct slide {
    void* view;
};


/** Creates a new deck with 'size' slides */
struct deck dk_new(int slide_count);
/** Frees all the slides and their contents */
void dk_free(struct deck* dk);

void debug_deck(const struct deck* deck);
void debug_slide(const struct slide* slide);
