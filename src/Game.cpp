#include "Game.hpp"

Game::Game(const Settings& settings)
    : window(sf::VideoMode({settings.windowWidth, settings.windowHeight}), settings.title)
    , grid(settings.gridOffset)
    , restartBtnRect({100.f, 100.f})
{
    std::array fontNames = {
        "./assets/fonts/Audiowide-Regular.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf",
        "c:/windows/fonts/arial.ttf"};
    
    if (std::none_of(fontNames.begin(), fontNames.end(), [this](const auto& filename){
        return font.openFromFile(filename);}))
    {
        throw std::runtime_error("Couldn't load font!");
    }

    restartBtnRect.setFillColor(sf::Color::Transparent);
    restartBtnRect.setPosition({600.f, 200.f});
    
    if (!restartBtnTexture.loadFromFile("./assets/images/restart_btn.png"))
    {
        throw std::runtime_error("Couldn't load image!");
    }

    restartBtn = std::optional<sf::Sprite>(restartBtnTexture);
    restartBtn->setScale({
        restartBtnRect.getSize().x / restartBtnTexture.getSize().x,
        restartBtnRect.getSize().y / restartBtnTexture.getSize().y
    });
    restartBtn->setPosition(restartBtnRect.getPosition());
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
    }
}

void Game::handleEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto& mouseButton = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButton->button == sf::Mouse::Button::Left)
            {
                if (!sessionOver())
                {
                    placeFigure(mouseButton->position);
                }
                else if (hoverRestartBtn(mouseButton->position))
                {
                    restart();
                }
            }
        }

        if (const auto& keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::R && sessionOver())
            {
                restart();
            }
        }
    }
}

void Game::render()
{
    window.clear(sf::Color(167, 185, 225));

    window.draw(grid);

    if (sessionOver())
    {
        displayWinner();
        showRestartBtn();
    }

    window.display();
}

bool Game::sessionOver() const
{
    return (winner != Figure::None) || grid.isFilled();
}

void Game::updateWinner()
{
    std::set<Figure> figures;
    for (const auto& line : winningLines)
    {
        for (const auto& coord : line)
        {
            figures.insert(grid(coord.first, coord.second).figure);
        }

        if (figures.size() < 2 && figures.find(Figure::None) == figures.end())
        {
            winner = figures.count(Figure::Cross) ? Figure::Cross : Figure::Circle;
            return;
        }

        figures.clear();
    }
}

void Game::placeFigure(const sf::Vector2i& mousePos)
{
    const Figure pending = crossMove ? Figure::Cross : Figure::Circle;
    const bool placedSuccessfully = grid.placeFigure(pending, window.mapPixelToCoords(mousePos));
    if (placedSuccessfully)
    {
        crossMove = !crossMove;
        updateWinner();
    }
}

void Game::displayWinner()
{
    sf::Text conclusion(font, "The winner is: " + to_string(winner));
    conclusion.setCharacterSize(30);
    conclusion.setStyle(sf::Text::Bold);
    
    switch(winner)
    {
        case Figure::None:
            conclusion.setFillColor(sf::Color(85, 74, 0));
            break;
        case Figure::Cross:
            conclusion.setFillColor(sf::Color(126, 51, 171));
            break;
        case Figure::Circle:
            conclusion.setFillColor(sf::Color(0, 87, 0));
            break;
    }

    window.draw(conclusion);
}

void Game::showRestartBtn()
{
    window.draw(restartBtnRect);
    window.draw(*restartBtn);
}

bool Game::hoverRestartBtn(const sf::Vector2i& mousePos) const
{
    const auto& worldMousePos = window.mapPixelToCoords(mousePos);
    const auto& btnPos = restartBtnRect.getPosition();
    const auto& btnSize = restartBtnRect.getSize();
    return worldMousePos.x >= btnPos.x && worldMousePos.y >= btnPos.y
        && worldMousePos.x <= btnPos.x + btnSize.x
        && worldMousePos.y <= btnPos.y + btnSize.y;
}

void Game::restart()
{
    winner = Figure::None;
    grid.clear();
}