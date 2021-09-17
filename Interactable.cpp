#include "Interactable.h"

Interactable::Interactable(void(*runWhenTriggered)(int), sf::IntRect interactionBounds, bool enabled) {
	this->interactionBounds = interactionBounds;
	this->runWhenTriggered = runWhenTriggered;
	this->enabled = enabled;
}

Interactable::~Interactable()
{
}

void Interactable::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool Interactable::TestBounds(sf::Vector2i position)
{
	return enabled && interactionBounds.contains(position);
}

void Interactable::Triggered(int value) {
	runWhenTriggered(value);
};
