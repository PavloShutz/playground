#include "Figure.hpp"

std::string to_string(Figure figure)
{
    switch(figure)
    {
        case Figure::Cross:
            return "cross";
        case Figure::Circle:
            return "circle";
        case Figure::None:
            return "none";
        default:
            return "unknown";
    }
}