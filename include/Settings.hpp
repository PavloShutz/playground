#ifndef _SETTINGS_HPP
#define _SETTINGS_HPP

#include <string>

#include <SFML/Graphics.hpp>

struct Settings
{
    unsigned int windowWidth, windowHeight;
    std::string title;
    sf::Vector2f gridOffset;
};

#endif  // _SETTINGS_HPP
