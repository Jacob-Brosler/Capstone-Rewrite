#include "Collidable.h"

void Collidable::SetPos(sf::Vector2f newPos)
{
	this->topLeft = newPos;
}

Collidable::Collidable(sf::Vector2f topLeft, sf::Vector2f size)
{
	this->topLeft = topLeft;
	this->size = size;
}

Collidable::~Collidable()
{
}

sf::Vector2f Collidable::GetPos()
{
	return topLeft;
}

sf::Vector2f Collidable::GetSize()
{
	return size;
}
