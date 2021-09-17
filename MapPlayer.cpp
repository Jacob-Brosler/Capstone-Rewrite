#include "MapPlayer.h"

MapPlayer::MapPlayer(sf::Vector2f topLeft, sf::Vector2f size)
{
	renderShape.setPosition(topLeft);
	renderShape.setSize(size);
	renderShape.setFillColor(sf::Color::Red);
	movespeed = 200;
	mapPosition = sf::Vector2f(0, 0);
}

MapPlayer::~MapPlayer()
{
}

int MapPlayer::GetMovespeed()
{
	return movespeed;
}

sf::Vector2f MapPlayer::GetDrawnPos()
{
	return renderShape.getPosition();
}

sf::Vector2f MapPlayer::GetTopLeft()
{
	return mapPosition;
}

sf::Vector2f MapPlayer::GetBottomRight()
{
	return mapPosition + renderShape.getSize();
}

void MapPlayer::SetPosition(sf::Vector2f pos)
{
	mapPosition = pos;
}

void MapPlayer::Move(sf::Vector2f movement)
{
	mapPosition += movement;
}

void MapPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(renderShape, states);
}
