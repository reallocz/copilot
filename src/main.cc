#include <iostream>
#include "display.h"


int main()
{
    Display display(640, 480);
    display.Start();

    Slide s1{0, "Slide 1", {255, 0, 0, 255}};
    Slide s2{0, "Slide 2", {0, 255, 0, 255}};
    Slide s3{0, "Slide 3", {0, 0, 255, 255}};

    Deck d;
    d.AddSlide(s1);
    d.AddSlide(s2);
    d.AddSlide(s3);

    display.SetDeck(&d);


    // Main loop
    while (display.Running()) {
        // Poll events
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
            case SDL_QUIT: display.SetQuit(true); break;
            case SDL_KEYUP:
                SDL_Keysym keysym = sdl_event.key.keysym;
                if (keysym.sym == SDLK_ESCAPE) {
                    display.SetQuit(true);
                } else if (keysym.sym == SDLK_RIGHT) {
                    d.GotoNext();
                } else if (keysym.sym == SDLK_LEFT) {
                    d.GotoPrev();
                }
                break;
            }
        }

        // Update display
        display.Update();
    }
    return 0;
}
