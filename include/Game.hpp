#ifndef _GAME_HPP
#define _GAME_HPP

#include <algorithm>
#include <array>
#include <optional>
#include <set>
#include <stdexcept>
#include <utility>

#include <SFML/Graphics.hpp>

#include "Figure.hpp"
#include "Grid.hpp"
#include "Settings.hpp"

class Game
{
public:
    explicit Game(const Settings& settings);

    void run();

    void handleEvents();

    void render();

    bool sessionOver() const;

    void updateWinner();

    void placeFigure(const sf::Vector2i& mousePos);

    void displayWinner();

    void showRestartBtn();

    bool hoverRestartBtn(const sf::Vector2i& mousePos) const;

    void restart();

private:
    sf::RenderWindow window;
    
    Grid grid;
    sf::Font font;
    Figure winner = Figure::None;

    // Restart button
    sf::RectangleShape restartBtnRect;
    sf::Texture restartBtnTexture;
    std::optional<sf::Sprite> restartBtn;

    bool crossMove = true;

    const std::array<std::array<std::pair<int, int>, DIMENSION>, 8> winningLines {{
        {{{0, 0}, {0, 1}, {0, 2}}},
        {{{1, 0}, {1, 1}, {1, 2}}},
        {{{2, 0}, {2, 1}, {2, 2}}},
        {{{0, 0}, {1, 0}, {2, 0}}},
        {{{0, 1}, {1, 1}, {2, 1}}},
        {{{0, 2}, {1, 2}, {2, 2}}},
        {{{0, 0}, {1, 1}, {2, 2}}},
        {{{0, 2}, {1, 1}, {2, 0}}}
    }};
};

#endif  // _GAME_HPP
