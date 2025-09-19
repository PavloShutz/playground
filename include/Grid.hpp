#ifndef _GRID_HPP
#define _GRID_HPP

#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Figure.hpp"
#include "Cell.hpp"

constexpr int DIMENSION = 3;

class Grid : public sf::Drawable
{
public:
    Grid(sf::Vector2f newPos = {});

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool placeFigure(Figure figure, const sf::Vector2f& mousePos);

    sf::Vector2f getPosition() const;

    bool isFilled() const;

    static int toIndex(int row, int col);

    Cell& operator()(int row, int col);

    void clear();

    bool contains(const sf::Vector2f& mousePos) const;

private:
    std::array<Cell, DIMENSION * DIMENSION> cells;
    sf::Vector2f pos;
};

#endif  // _GRID_HPP
