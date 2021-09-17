#ifndef MAP_H
#define MAP_H

#include <SFML/System.hpp>
#include <vector>
#include "Collidable.h"

class Map
{
private:
	sf::Vector2i mapSize;
	std::string mapTexture;
	int* map;
public:
	Map(int mapSizeX, int mapSizeY, int* map, std::string tilemap);
	~Map();

	std::string GetTilemapName();
	int GetWidth();
	int GetHeight();
	int GetCell(int x, int y);
	void ChangeCell(int x, int y, int newVal);
};

#endif