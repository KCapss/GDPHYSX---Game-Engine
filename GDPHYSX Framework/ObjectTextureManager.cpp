#include "ObjectTextureManager.h"
#include <iostream>

ObjectTextureManager* ObjectTextureManager::sharedInstance = NULL;

ObjectTextureManager* ObjectTextureManager::getInstance() {
	//initial only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new ObjectTextureManager();
	}

	return sharedInstance;

}
void ObjectTextureManager::loadAll()
{
	//with no texture
	loadObj("planet", "3D/planet.obj");
	loadObj("ship", "3D/shipPlayer.obj");

	//Loading for Obj
	loadObj("tower", "3D/towerDebri.obj");
	loadObj("generator", "3D/generatorDebri.obj");
	loadObj("statue2", "3D/statue2Debri.obj");
	loadObj("statue", "3D/statueDebri.obj");
	loadObj("spaceRock", "3D/spaceRockDebri.obj");
	
	//loadObj

	//Loading for Texture;
	loadTexture("ship", "3D/shipPlayerTexture.jpg");

	loadTexture("tower", "3D/towerDebriTexture.jpg");
	loadTexture("generator", "3D/generatorDebriTexture.jpg");
	loadTexture("statue2", "3D/statue2DebriTexture.jpg");
	loadTexture("statue", "3D/statueDebriTexture.jpg");
	loadTexture("spaceRock", "3D/spaceRockDebriTexture.jpg");

	//Load for Texture with Normal Map
	loadTexture("shipNormal", "3D/shipPlayerNormalTexture.jpg");
}

std::string ObjectTextureManager::getObjPath(std::string key)
{
	if (objPathMap.find(key) != objPathMap.end()) {
		return objPathMap[key];
	}

	else {
		std::cout << "No objPath found for " << key << std::endl;
		return NULL;
	}
	
}

std::string ObjectTextureManager::getTexturePath(std::string key)
{
	key = key + "Texture";
	if (texturePathMap.find(key) != texturePathMap.end()) {
		return texturePathMap[key];
	}

	else {
		std::cout << "No texturePath found for " << key << std::endl;
		return NULL;
	}

}



void ObjectTextureManager::loadObj(std::string key, std::string path)
{
	objPathMap[key] = path;
}

void ObjectTextureManager::loadTexture(std::string key, std::string path)
{
	texturePathMap[key + "Texture"] = path;
}

