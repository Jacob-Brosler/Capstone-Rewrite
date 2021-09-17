#include "Game.h"
#include "Registry.h"

Game::Game()
{
}

Game::~Game()
{
}

/// <summary>
/// Sets up the initial state of the game and starts the game loop
/// </summary>
void Game::Run()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Battle Test");
	window->setFramerateLimit(60);
	window->setKeyRepeatEnabled(false);

	Registry::LoadRegistry(window->getSize().x, window->getSize().y);

	playerSize = sf::Vector2f(46, 46);
	player = std::make_shared<MapPlayer>(
		sf::Vector2f((window->getSize().x - playerSize.x) / 2, (window->getSize().y - playerSize.y) / 2),
		playerSize);

	inputManager = std::make_shared<InputManager>();

	renderer = std::make_shared<Renderer>(window, player);

	//Load the starting map
	loadedMap = 1;
	renderedTileSize = 48;
	renderer->LoadMap(loadedMap, renderedTileSize);

	exiting = false;
	while (!exiting) {
		Update();
	}

	if (window->isOpen())
		window->close();
}

/// <summary>
/// Runs all of the game logic for each frame
/// Called once per frame
/// </summary>
void Game::Update()
{
	sf::Time deltaTime = deltaClock.restart();
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

	if (!renderer->UIOccludesMovement()) {
		//Check if player is trying to move
		sf::Vector2f playerMovement;
		if (inputManager->TestKeybind(InputManager::MapMoveUp)) {
			playerMovement += sf::Vector2f(0, -player->GetMovespeed());
		}
		if (inputManager->TestKeybind(InputManager::MapMoveDown)) {
			playerMovement += sf::Vector2f(0, player->GetMovespeed());
		}
		if (inputManager->TestKeybind(InputManager::MapMoveLeft)) {
			playerMovement += sf::Vector2f(-player->GetMovespeed(), 0);
		}
		if (inputManager->TestKeybind(InputManager::MapMoveRight)) {
			playerMovement += sf::Vector2f(player->GetMovespeed(), 0);
		}
		playerMovement *= deltaTime.asSeconds();

		//Check collisions
		//ASSUMES: Player size <= rendered tile size
		if (playerMovement != sf::Vector2f()) {
			const float futureLeft = player->GetTopLeft().x + playerMovement.x;
			const float futureRight = player->GetBottomRight().x + playerMovement.x;
			int leftTilePos = MapToTile(player->GetTopLeft().x);
			int rightTilePos = MapToTile(player->GetBottomRight().x);
			const int topTilePos = MapToTile(player->GetTopLeft().y);
			const int bottomTilePos = MapToTile(player->GetBottomRight().y);
			const int leftTileDiff = MapToTile(futureLeft) - leftTilePos;
			const int rightTileDiff = MapToTile(futureRight) - rightTilePos;
			//Player tries to move into a new tile horizontally
			if (leftTileDiff == -1) {
				//If it will collide, limit movement to edge of next cell
				if (CollidableAtTile(leftTilePos - 1, topTilePos) || fmod(player->GetBottomRight().y, renderedTileSize) != 0 && CollidableAtTile(leftTilePos - 1, bottomTilePos)) {
					playerMovement.x += renderedTileSize - fmod(futureLeft, renderedTileSize);
				}
			}
			else if (rightTileDiff == 1 || (int)fmod(player->GetBottomRight().x, renderedTileSize) == 0 && playerMovement.x > 0) {
				int nextTileX = rightTilePos + rightTileDiff;
				//If it will collide, limit movement to edge of next cell
				if (CollidableAtTile(nextTileX, topTilePos) || fmod(player->GetBottomRight().y, renderedTileSize) != 0 && CollidableAtTile(nextTileX, bottomTilePos)) {
					playerMovement.x -= fmod(futureRight, renderedTileSize);
				}
			}
			renderer->MoveMap(sf::Vector2f(-playerMovement.x, 0));
			player->Move(sf::Vector2f(playerMovement.x, 0));

			const float futureTop = player->GetTopLeft().y + playerMovement.y;
			const float futureBottom = player->GetBottomRight().y + playerMovement.y;
			leftTilePos = MapToTile(player->GetTopLeft().x);
			rightTilePos = MapToTile(player->GetBottomRight().x);
			const int topTileDiff = MapToTile(futureTop) - topTilePos;
			const int bottomTileDiff = MapToTile(futureBottom) - bottomTilePos;
			//Player tries to move into a new tile vertically
			if (topTileDiff == -1) {
				//If it will collide, limit movement to edge of next cell
				if (CollidableAtTile(leftTilePos, topTilePos - 1) || fmod(player->GetBottomRight().x, renderedTileSize) != 0 && CollidableAtTile(rightTilePos, topTilePos - 1)) {
					playerMovement.y += renderedTileSize - fmod(futureTop, renderedTileSize);
				}
			}
			else if (bottomTileDiff == 1 || (int)fmod(player->GetBottomRight().y, renderedTileSize) == 0 && playerMovement.y > 0) {
				//If it will collide, limit movement to edge of next cell
				int nextTileY = bottomTilePos + bottomTileDiff;
				if (CollidableAtTile(leftTilePos, nextTileY) || fmod(player->GetBottomRight().x, renderedTileSize) != 0 && CollidableAtTile(rightTilePos, nextTileY)) {
					playerMovement.y -= fmod(futureBottom, renderedTileSize);
				}
			}
			renderer->MoveMap(sf::Vector2f(0, -playerMovement.y));
			player->Move(sf::Vector2f(0, playerMovement.y));
		}
	}

	Draw();
	inputManager->EndFrame();
}

/// <summary>
/// Draws the current frame
/// </summary>
void Game::Draw()
{
	renderer->Draw();
}

/// <summary>
/// Maps a pixel position to a tile position on the map 
/// </summary>
/// <param name="mapPos">Position relative to the top left corner of the map</param>
/// <returns>Tile position relative to the top left corner of the map</returns>
int Game::MapToTile(float mapPos)
{
	return ((int)mapPos) / renderedTileSize;
}

/// <summary>
/// Returns if the given tile is collidable on the loaded map
/// </summary>
/// <param name="x">X pos in tile coords</param>
/// <param name="y">Y pos in tile coords</param>
/// <returns>If the tile is collidable</returns>
bool Game::CollidableAtTile(int x, int y)
{
	return Registry::tileCollidable[Registry::mapList[loadedMap]->GetCell(x, y)];
}
