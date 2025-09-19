#ifndef _CELL_HPP
#define _CELL_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

#include "Figure.hpp"

struct Cell : public sf::Drawable
{
    Cell();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f getRelativePosition() const;

    void drawCircle(sf::RenderTarget& target, sf::RenderStates states) const;

    void drawCross(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Vector2i coords;
    Figure figure;
    sf::RectangleShape rect;
    float size = 100.f;
};

#endif  // _CELL_HPP
