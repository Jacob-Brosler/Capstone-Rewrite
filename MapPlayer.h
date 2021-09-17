#ifndef MAPPLAYER_H
#define MAPPLAYER_H

#include <SFML/System.hpp>
#include "Collidable.h"

class MapPlayer : public sf::Drawable
{
private:
	sf::RectangleShape renderShape;
	sf::Vector2f mapPosition;
	int movespeed;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:

	MapPlayer(sf::Vector2f topLeft, sf::Vector2f size);
	~MapPlayer();

	int GetMovespeed();
	sf::Vector2f GetDrawnPos();
	sf::Vector2f GetTopLeft();
	sf::Vector2f GetBottomRight();
	void SetPosition(sf::Vector2f pos);
	void Move(sf::Vector2f movement);
};

#endif