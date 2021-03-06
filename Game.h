#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Renderer.h"
#include "InputManager.h"
#include "MapPlayer.h"
#include "CollisionManager.h"

class Game
{
private:
	sf::Event event;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<InputManager> inputManager;
	std::shared_ptr<CollisionManager> collisionManager;
	std::shared_ptr<MapPlayer> player;

	int loadedMap;
	int renderedTileSize;
	bool exiting;
	sf::Vector2f playerSize;

	sf::Clock deltaClock;

	void Update();
	void Draw();
	int MapToTile(float mapPos);
	bool CollidableAtTile(int x, int y);
public:
	Game();
	~Game();

	void Run();
};

#endif