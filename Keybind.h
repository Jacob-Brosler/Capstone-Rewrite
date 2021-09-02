#ifndef KEYBIND_H
#define KEYBIND_H

#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <algorithm>

class Keybind
{
public:
    //The keybinding will trigger if any of these keys were pressed this frame and the "must" conditions are met
    std::vector<sf::Keyboard::Key> triggerKeyPressed;
    //The keybinding will trigger if any of these keys were released this frame and the "must" conditions are met
    std::vector<sf::Keyboard::Key> triggerKeyReleased;
    //The keybinding will trigger if any of these keys are down this frame and the "must" conditions are met
    std::vector<sf::Keyboard::Key> triggerKeyDown;
    //All of these keys must be up for any of the triggers to work
    std::vector<sf::Keyboard::Key> mustHaveUp;
    //All of these keys must be down for any of the triggers to work
    std::vector<sf::Keyboard::Key> mustHaveDown;

    Keybind();

    Keybind(std::vector<sf::Keyboard::Key> triggerKeyPressed,
        std::vector<sf::Keyboard::Key> triggerKeyReleased = std::vector<sf::Keyboard::Key>(),
        std::vector<sf::Keyboard::Key> triggerKeyDown = std::vector<sf::Keyboard::Key>(),
        std::vector<sf::Keyboard::Key> mustHaveUp = std::vector<sf::Keyboard::Key>(),
        std::vector<sf::Keyboard::Key> mustHaveDown = std::vector<sf::Keyboard::Key>());
};

#endif