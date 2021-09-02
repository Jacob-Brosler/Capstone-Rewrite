#ifndef MAP_H
#define MAP_H

#include <SFML/System.hpp>
#include <vector>
#include "Collidable.h"

class Map
{
private:
	sf::Vector2i mapSize;
	int* map;
	std::vector<Collidable> collision;
public:
	Map();
	~Map();
};

#endif