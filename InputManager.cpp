#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update(sf::Event keyboardEvent)
{
    switch (keyboardEvent.type) 
    {
    case sf::Event::KeyPressed:
        if (std::find(downKeys.begin(), downKeys.end(), keyboardEvent.key.code) == downKeys.end()) {
            pressedKeys.push_back(keyboardEvent.key.code);
            downKeys.push_back(keyboardEvent.key.code);
        }
        break;
    case sf::Event::KeyReleased:
        downKeys.remove(keyboardEvent.key.code);
        releasedKeys.push_back(keyboardEvent.key.code);
        break;
    }
}

void InputManager::EndFrame()
{
    pressedKeys.clear();
    releasedKeys.clear();
}

bool InputManager::TestKeybind(PlayerKeybinds keybind)
{
    for(sf::Keyboard::Key key : keybinds[keybind].mustHaveDown)
    {
        if (!sf::Keyboard::isKeyPressed(key))
            return false;
    }
    for(sf::Keyboard::Key key : keybinds[keybind].mustHaveUp)
    {
        if (sf::Keyboard::isKeyPressed(key))
            return false;
    }
    std::sort(pressedKeys.begin(), pressedKeys.end());
    for(sf::Keyboard::Key key : keybinds[keybind].triggerKeyPressed)
    {
        if (std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end())
            return true;
    }
    std::sort(releasedKeys.begin(), releasedKeys.end());
    for (sf::Keyboard::Key key : keybinds[keybind].triggerKeyReleased)
    {
        if (std::find(releasedKeys.begin(), releasedKeys.end(), key) != releasedKeys.end())
            return true;
    }
    for(sf::Keyboard::Key key : keybinds[keybind].triggerKeyDown)
    {
        if (sf::Keyboard::isKeyPressed(key))
            return true;
    }
    return false;
}
