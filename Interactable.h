#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <SFML/Graphics.hpp>

class Interactable
{
private:
	sf::IntRect interactionBounds;
	bool enabled;

	void (*runWhenTriggered)(int) = {};
public:
	Interactable(void (*runWhenTriggered)(int), sf::IntRect interactionBounds, bool enabled = true);
	~Interactable();

	void SetEnabled(bool enabled);
	bool TestBounds(sf::Vector2i position);
	void Triggered(int value);
};

#endif