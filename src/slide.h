#pragma once
#include <string>

struct Color
{
    uint8_t r, g, b, a;
};

class Slide
{
public:
    unsigned int number;
    std::string text;
    Color color;
};
