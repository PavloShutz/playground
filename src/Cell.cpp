#include "Cell.hpp"

Cell::Cell()
    : coords()
    , figure(Figure::None)
{
    rect.setSize({size, size});
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(-3.f);
    rect.setOutlineColor(sf::Color::White);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rect, states);
    switch(figure)
    {
        case Figure::Cross:
        {
            drawCross(target, states);
            break;
        }
        case Figure::Circle:
        {
            drawCircle(target, states);
            break;
        }
        case Figure::None:
        default:
            break;
    }
}

sf::Vector2f Cell::getRelativePosition() const
{
    return sf::Vector2f(coords.x * size, coords.y * size);
}

void Cell::drawCircle(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto circle = sf::CircleShape(size / 2);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(-10.f);
    circle.setOutlineColor(sf::Color::White);
    circle.setPosition(getRelativePosition());
    target.draw(circle, states);
}

void Cell::drawCross(sf::RenderTarget& target, sf::RenderStates states) const
{
    const auto sqrt2 = static_cast<float>(std::sqrt(2.f));
    auto line1 = sf::RectangleShape({size * sqrt2, 10.f});
    auto line2 = sf::RectangleShape({size * sqrt2, 10.f});

    line1.setFillColor(sf::Color::Red);
    line2.setFillColor(sf::Color::Red);

    line1.rotate(sf::degrees(45.f));
    line2.rotate(sf::degrees(135.f));

    line1.setPosition(getRelativePosition());
    line2.setPosition(getRelativePosition() + sf::Vector2f(size, 0.f));

    target.draw(line1, states);
    target.draw(line2, states);
}