#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "UIDefinition.h"
#include "MapPlayer.h"

class Renderer
{
private:
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<MapPlayer> player;

	std::vector<int> loadedUI;

	int loadedMap;
	int tileSizePx;
	int renderedTileSizePx;
	sf::RenderStates mapState;
	std::shared_ptr<sf::VertexArray> mapRender;
public:
	Renderer(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapPlayer> player);
	~Renderer();

	void Draw();
	void LoadMap(int mapID, int renderedTileSize);
	void SetMapPos(sf::Vector2f pos);
	void MoveMap(sf::Vector2f movement);
	bool UIOccludesMap();
	bool UIOccludesMovement();
	void LoadUI(int ui);
	void UnloadUI(int ui);
};

#endif