#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
#if defined(DEBUG) | defined(_DEBUG)
    // Enable memory leak detection as a quick and dirty
    // way of determining if we forgot to clean something up
    // You may want to use something more advanced, like Visual Leak Detector
    // - Courtesy of Chris Cascioli
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Game game;
    game.Run();

    return 0;
}