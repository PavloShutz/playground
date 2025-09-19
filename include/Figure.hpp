#ifndef _FIGURE_HPP
#define _FIGURE_HPP

#include <string>

enum class Figure
{
    None,
    Cross,
    Circle
};

std::string to_string(Figure figure);

#endif  // _FIGURE_HPP
