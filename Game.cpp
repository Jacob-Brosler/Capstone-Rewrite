#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Run()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Battle Test");
	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);

	player = std::make_shared<MapPlayer>(sf::Vector2f(20, 20), sf::Vector2f(100, 100));

	inputManager = std::make_shared<InputManager>();

	exiting = false;
	while (!exiting) {
		Update();
	}

	if (window->isOpen())
		window->close();
}

void Game::Update()
{
	while (window->pollEvent(event)) {
		switch (event.type) 
		{
		case sf::Event::Closed:
			window->close();
		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
			inputManager->Update(event);
			break;
		}
	}
	if (inputManager->TestKeybind(InputManager::MapMoveUp))
		player->Move(sf::Vector2f(0, -3));
	if (inputManager->TestKeybind(InputManager::MapMoveDown))
		player->Move(sf::Vector2f(0, 3));
	if (inputManager->TestKeybind(InputManager::MapMoveLeft))
		player->Move(sf::Vector2f(-3, 0));
	if (inputManager->TestKeybind(InputManager::MapMoveRight))
		player->Move(sf::Vector2f(3, 0));
	Draw();
	inputManager->EndFrame();
}

void Game::Draw()
{
	window->clear();
	window->draw(*player);
	window->display();
}
