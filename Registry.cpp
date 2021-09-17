#include "Registry.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

std::map<std::string, std::shared_ptr<sf::Texture>> Registry::textureStorage;
std::vector<std::shared_ptr<UIDefinition>> Registry::uiList;
std::vector<std::shared_ptr<Map>> Registry::mapList;
std::vector<bool> Registry::tileCollidable;

const std::string Registry::dataBasePath = "Resources/Data/";
const std::string Registry::mapLoadFile = "maps.csv";

void Registry::LoadRegistry(int windowWidth, int windowHeight)
{
	//Loads all of the textures

	std::shared_ptr<sf::Texture> uiBlank = std::make_shared<sf::Texture>();
	if (!uiBlank->loadFromFile("Resources/UI/uiBlank.png")) {
		std::cout << "Failed to load solid color ui texture.";
	}
	textureStorage.emplace("UI_Solid", uiBlank);

	std::shared_ptr<sf::Texture> spritesheet = std::make_shared<sf::Texture>();
	if (!spritesheet->loadFromFile("Resources/SpriteSheet.png")) {
		std::cout << "Failed to load map tile sheet.";
	}
	textureStorage.emplace("MAP_Tilemap", spritesheet);

	//Generates all UIs

	//Test UI
	uiList.emplace_back(
		std::make_shared<UIDefinition>(
			false,
			false,
			std::vector<std::shared_ptr<UISprite>>{
				std::make_shared<UISprite>(sf::IntRect(200, 200, 50, 50), textureStorage["UI_Solid"], sf::Color::Yellow, sf::IntRect(),
					std::vector<std::shared_ptr<UISprite>>{
						std::make_shared<UISprite>(sf::IntRect(100, 100, 50, 50), textureStorage["UI_Solid"], sf::Color::Blue),
						std::make_shared<UISprite>(sf::IntRect(-100, -100, 50, 50), textureStorage["UI_Solid"], sf::Color::Blue)
					}
				)
			}
		)
	);

	//Loads the maps

	std::fstream mapFile;

	mapFile.open(dataBasePath + mapLoadFile, std::ios::in);

	//First line is amount of maps to load
	std::string mapCount, mapSizeL, mapCellLine, tilemap;
	std::getline(mapFile, mapCount);
	for (int i = 0; i < std::stoi(mapCount); i++) 
	{
		//First line of each map is the size
		std::getline(mapFile, mapSizeL);
		sf::Vector2i mapSize = sf::Vector2i(
			std::stoi(mapSizeL.substr(0, mapSizeL.find(","))), 
			std::stoi(mapSizeL.substr(mapSizeL.find(",") + 1, mapSizeL.length())));

		//Now for the actual map layout
		int* mapLayout = new int[mapSize.x * mapSize.y];
		for (int y = 0; y < mapSize.y; y++) 
		{
			std::getline(mapFile, mapCellLine);
			for (int x = 0; x < mapSize.x; x++)
			{
				mapLayout[x + y * mapSize.y] = std::stoi(mapCellLine.substr(0, mapCellLine.find(",")));
				//No need to remove a comma on the last pull
				if(x != mapSize.x - 1)
					mapCellLine.erase(0, mapCellLine.find(",") + 1);
			}
		}
		//Get the tilemap to use
		std::getline(mapFile, tilemap);

		//Add the map to the vector
		mapList.emplace_back(std::make_shared<Map>(mapSize.x, mapSize.y, mapLayout, tilemap));
	}

	//Writes the tile type collisions
	tileCollidable = {
		false,
		false,
		true,
		true,
		true,
		true,
		false,
		true,
		false,
		true,
		true,
		false,
		false,
		true,
		false,
		false,
		false,
		false
	};
}
