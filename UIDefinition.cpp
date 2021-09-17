#include "UIDefinition.h"

void UIDefinition::GenerateInteractionList(std::shared_ptr<UISprite> sprite)
{
	if (std::shared_ptr<Interactable> interactable = std::dynamic_pointer_cast<Interactable>(sprite)) {
		interactables.emplace_back(interactable);
	}
	for (std::shared_ptr<UISprite> s : sprite->GetChildren()) {
		GenerateInteractionList(s);
	}
}

UIDefinition::UIDefinition(bool occludesMap, bool occludesMovement, std::vector<std::shared_ptr<UISprite>> children) : UISprite({}, {}, sf::Color::White, {}, children)
{
	this->occludesMap = occludesMap;
	this->occludesMovement = occludesMovement;
}

UIDefinition::~UIDefinition()
{
}

bool UIDefinition::OccludesMap()
{
	return occludesMap;
}

bool UIDefinition::OccludesMovement()
{
	return occludesMovement;
}
