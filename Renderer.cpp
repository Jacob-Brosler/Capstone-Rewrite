#include "Renderer.h"
#include <iostream>
#include "Registry.h"

void Renderer::Draw()
{
	window->clear();
	if (!UIOccludesMap()) {
		window->draw(*mapRender, mapState);
		window->draw(*player);
	}
	for (int ui : loadedUI) {
		window->draw(*Registry::uiList[ui]);
	}
	window->display();
}

void Renderer::LoadMap(int mapID, int renderedTileSize)
{
	loadedMap = mapID;
	renderedTileSizePx = renderedTileSize;
	mapState.texture = Registry::textureStorage[Registry::mapList[loadedMap]->GetTilemapName()].get();
	SetMapPos(player->GetDrawnPos() - sf::Vector2f(96, 96));
	mapRender->clear();

	for (int i = 0; i < Registry::mapList[loadedMap]->GetWidth(); i++) {
		for (int j = 0; j < Registry::mapList[loadedMap]->GetHeight(); j++) {
			// - 1 makes later math easier
			int mapCell = Registry::mapList[loadedMap]->GetCell(i, j) - 1;
			if (mapCell != -1) {
				int x = (mapCell % 3) * tileSizePx;
				int y = (mapCell / 3) * tileSizePx;
				mapRender->append(sf::Vertex(sf::Vector2f(i * renderedTileSizePx, j * renderedTileSizePx), sf::Vector2f(x, y)));
				mapRender->append(sf::Vertex(sf::Vector2f((i + 1) * renderedTileSizePx, j * renderedTileSizePx), sf::Vector2f(x + tileSizePx, y)));
				mapRender->append(sf::Vertex(sf::Vector2f((i + 1) * renderedTileSizePx, (j + 1) * renderedTileSizePx), sf::Vector2f(x + tileSizePx, y + tileSizePx)));
				mapRender->append(sf::Vertex(sf::Vector2f(i * renderedTileSizePx, (j + 1) * renderedTileSizePx), sf::Vector2f(x, y + tileSizePx)));
			}
		}
	}
}

void Renderer::SetMapPos(sf::Vector2f pos)
{
	mapState = sf::RenderStates();
	MoveMap(pos);
	mapState.texture = Registry::textureStorage[Registry::mapList[loadedMap]->GetTilemapName()].get();
	player->SetPosition(player->GetDrawnPos() - pos);
}

void Renderer::MoveMap(sf::Vector2f movement)
{
	mapState.transform.translate(movement);
}

bool Renderer::UIOccludesMap()
{
	for (int ui : loadedUI) {
		if (Registry::uiList[ui]->OccludesMap())
			return true;
	}
	return false;
}

bool Renderer::UIOccludesMovement()
{
	for (int ui : loadedUI) {
		if (Registry::uiList[ui]->OccludesMovement())
			return true;
	}
	return false;
}

void Renderer::LoadUI(int ui)
{
	loadedUI.push_back(ui);
}

void Renderer::UnloadUI(int ui)
{
	for (int i = 0; i < loadedUI.size(); i++) {
		if (loadedUI[i] == ui)
			loadedUI.erase(loadedUI.begin() + i);
	}
}

Renderer::Renderer(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<MapPlayer> player)
{
	this->window = window;
	this->player = player;

	LoadUI(0);
	tileSizePx = 16;

	mapRender = std::make_shared<sf::VertexArray>();
	mapRender->setPrimitiveType(sf::Quads);
	mapRender->clear();

}

Renderer::~Renderer()
{
}
