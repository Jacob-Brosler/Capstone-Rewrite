#include "Keybind.h"

Keybind::Keybind()
{
}

Keybind::Keybind(std::vector<sf::Keyboard::Key> triggerKeyPressed,
    std::vector<sf::Keyboard::Key> triggerKeyReleased,
    std::vector<sf::Keyboard::Key> triggerKeyDown,
    std::vector<sf::Keyboard::Key> mustHaveUp,
    std::vector<sf::Keyboard::Key> mustHaveDown)
{
    this->triggerKeyPressed = triggerKeyPressed;
    std::sort(this->triggerKeyPressed.begin(), this->triggerKeyPressed.end());
    this->triggerKeyReleased = triggerKeyReleased;
    std::sort(this->triggerKeyReleased.begin(), this->triggerKeyReleased.end());
    this->triggerKeyDown = triggerKeyDown;
    this->mustHaveUp = mustHaveUp;
    this->mustHaveDown = mustHaveDown;
}