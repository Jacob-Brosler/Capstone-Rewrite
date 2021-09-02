#ifndef INPUTM_H
#define INPUTM_H

#include <SFML/Window.hpp>
#include <map>
#include <list>
#include "Keybind.h"

class InputManager
{
public:
    /// <summary>
    /// All possible actions that can be triggered by a key press
    /// </summary>
    enum PlayerKeybinds
    {
        MapMoveUp,
        MapMoveDown,
        MapMoveLeft,
        MapMoveRight,
        MapInteract,
        UIOpenPause,
        UIOpenInventory,
        UIBack,
        UIContinueText,
        UISkipText
    };

    InputManager();
    ~InputManager();

    void Update(sf::Event keyboardEvent);
    void EndFrame();
    bool TestKeybind(PlayerKeybinds keybind);
private:
    std::vector<sf::Keyboard::Key> pressedKeys;
    std::list<sf::Keyboard::Key> downKeys;
    std::vector<sf::Keyboard::Key> releasedKeys;

    std::map<PlayerKeybinds, Keybind> keybinds
    {
        {
            PlayerKeybinds::MapMoveUp,
            Keybind(
                {}, 
                {},
                std::vector<sf::Keyboard::Key>{ sf::Keyboard::W }, 
                std::vector<sf::Keyboard::Key>{ sf::Keyboard::S },
                {}
            )
        },
        {
            PlayerKeybinds::MapMoveDown,
            Keybind(
                {},
                {},
                std::vector<sf::Keyboard::Key>{ sf::Keyboard::S },
                std::vector<sf::Keyboard::Key>{ sf::Keyboard::W },
                {}
            )
        },
        {
            PlayerKeybinds::MapMoveLeft,
            Keybind(
                {},
                {},
                std::vector<sf::Keyboard::Key>{ sf::Keyboard::A },
                std::vector<sf::Keyboard::Key>{ sf::Keyboard::D },
                {}
            )
        },
        {
            PlayerKeybinds::MapMoveRight,
            Keybind(
                {},
                {},
                std::vector<sf::Keyboard::Key>{ sf::Keyboard::D },
                std::vector<sf::Keyboard::Key>{ sf::Keyboard::A },
                {}
            )
        },
    };
};

#endif