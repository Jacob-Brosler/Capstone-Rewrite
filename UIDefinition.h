#ifndef UIDEF_H
#define UIDEF_H

#include "UISprite.h"
#include "Interactable.h"

class UIDefinition : public UISprite
{
private:
	std::vector<std::shared_ptr<Interactable>> interactables;
	bool occludesMovement;
	bool occludesMap;

	void GenerateInteractionList(std::shared_ptr<UISprite> sprite);
public:
	UIDefinition(bool occludesMap, bool occludesMovement, std::vector<std::shared_ptr<UISprite>> children = {});
	~UIDefinition();

	bool OccludesMap();
	bool OccludesMovement();
};

#endif