#include "Grid.hpp"

Grid::Grid(sf::Vector2f newPos)
    : pos(newPos)
{
    for (int i = 0; i < DIMENSION; ++i)
    {
        for (int j = 0; j < DIMENSION; ++j)
        {
            auto& cell = cells[toIndex(i, j)];
            cell.coords = {i, j};
            cell.rect.setPosition(
                cell.getRelativePosition()
            );
        }
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.translate(pos);
    
    std::for_each(cells.begin(), cells.end(), [states, &target](const auto& cell){
        target.draw(cell, states);
    });
}

bool Grid::placeFigure(Figure figure, const sf::Vector2f& mousePos)
{
    if (!contains(mousePos))
    {
        return false;
    }

    const sf::Vector2i coords = {
        static_cast<int>((mousePos.x - pos.x) / cells[0].size),
        static_cast<int>((mousePos.y - pos.y) / cells[0].size)
    };

    const int index = toIndex(coords.x, coords.y);
    if (index < 0 || index >= cells.size())
    {
        return false;
    }

    auto& cell = cells[index];
    
    if (cell.figure != Figure::None)
    {
        return false;
    }

    cell.figure = figure;
    return true;
}

sf::Vector2f Grid::getPosition() const
{
    return pos;
}

bool Grid::isFilled() const
{
    return !std::any_of(cells.begin(), cells.end(), [](const auto& cell){
        return cell.figure == Figure::None;
    });
}

int Grid::toIndex(int row, int col)
{
    return DIMENSION * row + col;
}

Cell& Grid::operator()(int row, int col)
{
    const int index = toIndex(row, col);
    assert(index >= 0 && index < cells.size());
    return cells[index];
}

void Grid::clear()
{
    std::for_each(cells.begin(), cells.end(), [](auto& cell){
        cell.figure = Figure::None;
    });
}

bool Grid::contains(const sf::Vector2f& mousePos) const
{
    const sf::Vector2f bottomRightEdge = {
        cells.back().getRelativePosition() + 2.f * pos
    };
    
    if ((mousePos.x < pos.x || mousePos.y < pos.y) ||
        (mousePos.x > bottomRightEdge.x || mousePos.y > bottomRightEdge.y))
    {
        return false;
    }

    return true;
}