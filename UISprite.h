#ifndef UISPRITE_H
#define UISPRITE_H

#include <SFML/Graphics.hpp>

class UISprite : public sf::Drawable, public sf::Transformable
{
private:
	std::shared_ptr<sf::Texture> texture;
	sf::Sprite sprite;
	std::vector<std::shared_ptr<UISprite>> children;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	bool isVisible;

	UISprite(sf::IntRect boundingRect, std::shared_ptr<sf::Texture> texture = {}, sf::Color color = sf::Color::White, sf::IntRect subsection = {}, std::vector<std::shared_ptr<UISprite>> children = {});
	~UISprite();

	void AddChild(std::shared_ptr<UISprite> child);
	std::vector<std::shared_ptr<UISprite>> GetChildren();
	void SetVisible(bool visible);
};

#endif