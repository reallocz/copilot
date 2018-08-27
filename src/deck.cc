#include "deck.h"


Deck::Deck()
{
    current_slide_ = 0;
}

Deck::~Deck() {}

// Add slide at the end of the deck
void Deck::AddSlide(Slide slide)
{
    slides_.push_back(slide);
}
// Sets the next slide in deck as the current one
void Deck::GotoNext()
{
    if (current_slide_ < slides_.size() - 1) { ++current_slide_; }
}
// Sets the prev slide in deck as the current one
void Deck::GotoPrev()
{
    if (current_slide_ > 0) { --current_slide_; }
}
