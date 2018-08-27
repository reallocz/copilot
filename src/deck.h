#pragma once
#include <vector>
#include "slide.h"

/** A deck is a collection on slides */
class Deck
{
private:
    // Track current slide
    unsigned int current_slide_;
    std::vector<Slide> slides_;

public:
    Deck();
    ~Deck();

    // Add slide at the end of the deck
    void AddSlide(Slide slide);
    // Returns reference to current slide
    const Slide& CurrentSlide() const { return slides_[current_slide_]; }
    // Returns current slide number
    unsigned int CurrentSlideNumber() const { return current_slide_; }
    // Returns count of slides in the deck
    unsigned int SlideCount() const { return slides_.size(); }
    // Sets the next slide in deck as the current one
    void GotoNext();
    // Sets the prev slide in deck as the current one
    void GotoPrev();
};
