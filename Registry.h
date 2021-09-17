#pragma once
#include <vector>
#include <map>
#include "UIDefinition.h"
#include "Map.h"

class Registry
{
private:
	static const std::string dataBasePath;
	static const std::string mapLoadFile;
public:
	static std::map<std::string, std::shared_ptr<sf::Texture>> textureStorage;
	static std::vector<std::shared_ptr<UIDefinition>> uiList;
	static std::vector<std::shared_ptr<Map>> mapList;
	static std::vector<bool> tileCollidable;

	static void LoadRegistry(int windowWidth, int windowHeight);
};

