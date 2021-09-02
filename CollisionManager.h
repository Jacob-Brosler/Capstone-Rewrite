#ifndef COLLISIONM_H
#define COLLISIONM_H

#include <vector>
#include <memory>
#include "Collidable.h"
#include "MapPlayer.h"

class CollisionManager
{
private:
	std::shared_ptr<MapPlayer> player;
	std::vector<Collidable> collidables;
public:
	CollisionManager();
	~CollisionManager();
	void Update();
};

#endif