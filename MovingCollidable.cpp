#include "MovingCollidable.h"

MovingCollidable::MovingCollidable(sf::Vector2f topLeft, sf::Vector2f size) : Collidable(topLeft, size)
{
    hasUnregisteredMovement = false;
}

MovingCollidable::~MovingCollidable()
{
}

void MovingCollidable::Move(sf::Vector2f amount)
{
    Collidable::SetPos(GetPos() + amount);
    hasUnregisteredMovement = true;
}
