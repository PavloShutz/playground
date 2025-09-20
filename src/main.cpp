#include "Game.hpp"
#include "Settings.hpp"

#ifdef WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
#else
int main()
#endif
{
    const Settings settings{
        .windowWidth = 800u,
        .windowHeight = 600u,
        .title = "Tic-Tac-Toe",
        .gridOffset = {100.f, 100.f}
    };

    Game game{ settings };

    game.run();

    return EXIT_SUCCESS;
}