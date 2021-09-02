#ifndef MCOLLIDABLE_H
#define MCOLLIDABLE_H

#include <SFML/System.hpp>
#include "Collidable.h"

class MovingCollidable : public Collidable
{
private:
protected:
	float moveSpeed;

public:
	bool hasUnregisteredMovement;

	MovingCollidable(sf::Vector2f topLeft, sf::Vector2f size);
	~MovingCollidable();
	void Move(sf::Vector2f amount);
};

#endif