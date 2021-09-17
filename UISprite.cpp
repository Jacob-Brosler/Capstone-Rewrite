#include "UISprite.h"

void UISprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (isVisible) {
		target.draw(sprite, states);
		for (std::shared_ptr<UISprite> s : children) {
			s->draw(target, states);
		}
	}
}

UISprite::UISprite(sf::IntRect boundingRect, std::shared_ptr<sf::Texture> texture, sf::Color color, sf::IntRect subsection, std::vector<std::shared_ptr<UISprite>> children)
{
	setPosition(boundingRect.left, boundingRect.top);
	isVisible = true;
	this->children = children;
	sprite.setScale(boundingRect.width, boundingRect.height);
	if(texture != NULL)
		sprite.setTexture(*texture);
	if(color != sf::Color::White)
		sprite.setColor(color);
	if (subsection != sf::IntRect())
		sprite.setTextureRect(subsection);
}

UISprite::~UISprite()
{
}

void UISprite::AddChild(std::shared_ptr<UISprite> child)
{
	children.emplace_back(child);
}

std::vector<std::shared_ptr<UISprite>> UISprite::GetChildren()
{
	return children;
}

void UISprite::SetVisible(bool visible)
{
	isVisible = visible;
}
