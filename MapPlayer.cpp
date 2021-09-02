#include "MapPlayer.h"

MapPlayer::MapPlayer(sf::Vector2f topLeft, sf::Vector2f size) : MovingCollidable(topLeft, size)
{
	renderShape.setPosition(topLeft);
	renderShape.setSize(size);
	renderShape.setFillColor(sf::Color::Red);
}

MapPlayer::~MapPlayer()
{
}

void MapPlayer::Update()
{
}

void MapPlayer::Move(sf::Vector2f amount)
{
	renderShape.move(amount);
	MovingCollidable::Move(amount);
}

void MapPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(renderShape, states);
}
