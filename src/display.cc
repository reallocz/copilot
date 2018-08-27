#include "display.h"
#include <iostream>

constexpr auto PDEF_TITLE = "Untitled Window";

Display::Display(unsigned int width, unsigned int height)
{
    quit_   = false;
    width_  = width;
    height_ = height;
    title_  = PDEF_TITLE;
    deck_   = nullptr;
}

Display::~Display()
{
    SDL_DestroyRenderer(sdl_renderer_);
    SDL_DestroyWindow(sdl_window_);
    SDL_Quit();
}


void Display::SetDeck(Deck* deck)
{
    deck_ = deck;
}

void Display::Start()
{
    int err;
    // Init sdl
    err = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS |
                   SDL_INIT_TIMER);
    if (err != 0) {
        std::cerr << "Error!!" << std::endl;
        SDL_Log("Unable to init sdl: %s", SDL_GetError());
    }

    // Create sdl_window_
    sdl_window_ = SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, width_, height_, 0);
    if (sdl_window_ == NULL) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        throw std::runtime_error("Failed to create window!");
    }

    // Create sdl_renderer_
    sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, 0);
    if (sdl_renderer_ == NULL) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        throw std::runtime_error("Failed to create renderer!");
    }

    std::cout << "Display initialized successfully!" << std::endl;
}


void Display::Update()
{
    // Clear screen in black
    SDL_SetRenderDrawColor(sdl_renderer_, 210, 0, 0, 55);
    SDL_RenderClear(sdl_renderer_);

    if (deck_ != nullptr) {
        // Draw start
        const Slide& slide = deck_->CurrentSlide();
        //// Paint bg
        const Color c = slide.color;
        SDL_SetRenderDrawColor(sdl_renderer_, c.r, c.g, c.b, c.a);
        SDL_RenderClear(sdl_renderer_);
    }

    //// Paint fps

    // Draw end

    // Update!
    SDL_RenderPresent(sdl_renderer_);
    SDL_Delay(200);    // TODO remove!
}


void Display::SetQuit(bool flag)
{
    std::cout << "Quit flag set" << std::endl;
    quit_ = flag;
}
