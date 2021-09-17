#include "Map.h"

Map::Map(int mapSizeX, int mapSizeY, int* map, std::string tilemap)
{
	mapSize = sf::Vector2i(mapSizeX, mapSizeY);
	this->map = map;
	mapTexture = tilemap;
}

Map::~Map()
{
	delete[] map;
}

std::string Map::GetTilemapName()
{
	return mapTexture;
}

int Map::GetWidth()
{
	return mapSize.x;
}

int Map::GetHeight()
{
	return mapSize.y;
}

int Map::GetCell(int x, int y)
{
	//Makes sure the request is in bounds
	if(x >= 0 && x < mapSize.x && y >= 0 && y < mapSize.y)
		return map[x + y * mapSize.y];
	//If it isn't, return 0 since 0 is an empty tile
	return 0;
}

void Map::ChangeCell(int x, int y, int newVal)
{
	map[x + y * mapSize.y] = newVal;
}
