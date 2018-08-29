#include <stdio.h>
#include "string.h"
#include "window.h"


// TODO
// add sdl2ttf support
// finalize source slide format
// figure out custom layouts in a slide

struct deck demo_deck();

int main()
{
    struct window* window = win_new(640, 480);
    win_start(window);

    struct deck deck = demo_deck();
    window->deck     = &deck;

    // Main loop
    int should_render = 1;    // Render only on input!
    while (!window->quit) {
        // Poll events
        SDL_Event sdl_event;

        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
            case SDL_QUIT: window->quit = 1; break;
            case SDL_KEYUP: {
                should_render = 1;
                SDL_Keysym keysym = sdl_event.key.keysym;
                if (keysym.sym == SDLK_ESCAPE) {
                    window->quit = 1;
                } else if (keysym.sym == SDLK_RIGHT) {
                    if (window->deck->pointer < window->deck->slide_count - 1) {
                        window->deck->pointer++;
                    }
                } else if (keysym.sym == SDLK_LEFT) {
                    if (window->deck->pointer > 0) { window->deck->pointer--; }
                }
            }
            }
        }

        // Update display
        if (should_render == 1) {
            win_update(window);
            should_render = 0;
        }
    }

    return 0;
}


char* sample_strings[] = {"Slide 1", "This is slide 2",
                          "Slide 3 on the house!"};

struct deck demo_deck()
{
    struct deck deck;
    deck.slides      = malloc(3 * sizeof(struct slide));
    deck.slide_count = 3;
    deck.pointer     = 0;
    for (int i = 0; i < deck.slide_count; ++i) {
        struct slide* slide = &deck.slides[i];
        slide->init         = 1;
        slide->color        = (struct color){i * 70, (i - 20) * 50, 0, 255};
        slide->text         = str_new(0);
        str_set(&slide->text, sample_strings[i]);
    }
    return deck;
}
