#pragma once
#include <string>
#include "SDL2/SDL.h"

class Display
{
private:
    // Quit flag
    bool quit_;

    // Dimensions and title
    unsigned int width_, height_;
    std::string title_;

    // SDL stuff
    SDL_Window* sdl_window_;
    SDL_Renderer* sdl_renderer_;

public:
    Display(unsigned int width, unsigned int height);
    ~Display();

    // Open up the window
    void Start();
    // Update every frame
    void Update();
    // Set the quit flag
    void SetQuit(bool flag);
    // Return true if running
    bool Running() const { return !quit_; }
};
