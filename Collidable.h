#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Collidable
{
private:
	sf::Vector2f topLeft, size;
protected:
	void SetPos(sf::Vector2f newPos);
public:
	Collidable(sf::Vector2f topLeft, sf::Vector2f size);
	~Collidable();
	
	sf::Vector2f GetPos();
	sf::Vector2f GetSize();
};

#endif