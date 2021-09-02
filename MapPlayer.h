#ifndef MAPPLAYER_H
#define MAPPLAYER_H

#include <SFML/System.hpp>
#include "MovingCollidable.h"

class MapPlayer : public MovingCollidable, public sf::Drawable
{
private:
	sf::RectangleShape renderShape;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	MapPlayer(sf::Vector2f topLeft, sf::Vector2f size);
	~MapPlayer();

	void Update();
	void Move(sf::Vector2f amount);
};

#endif