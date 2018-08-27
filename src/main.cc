#include <iostream>
#include "display.h"


int main()
{
    Display display(640, 480);
    display.Start();

    // Main loop
    while (display.Running()) {
        // Poll events
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
            case SDL_QUIT: display.SetQuit(true); break;
            case SDL_KEYUP:
                SDL_Keysym keysym = sdl_event.key.keysym;
                if (keysym.sym == SDLK_ESCAPE) { display.SetQuit(true); }
                break;
            }
        }

        // Update display
        display.Update();
    }
    return 0;
}
