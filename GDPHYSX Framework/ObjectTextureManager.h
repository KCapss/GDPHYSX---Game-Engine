#pragma once
#include <string>
#include <unordered_map>

//SINGLETON DESIGN PATTERN

class ObjectTextureManager
{
	typedef std::unordered_map<std::string, std::string> un_map;

public:

	static ObjectTextureManager* getInstance();

	void loadAll();
	std::string getObjPath(std::string name);
	std::string getTexturePath(std::string name);


private:
	
	// set constructor to private
	ObjectTextureManager() {};

	// set copy constructor to private
	ObjectTextureManager(ObjectTextureManager const&) {}

	// assignment operator is private
	ObjectTextureManager& operator=(ObjectTextureManager const&) {};

	static ObjectTextureManager* sharedInstance;


	
	void loadObj(std::string key, std::string path);
	void loadTexture(std::string key, std::string path);
	un_map objPathMap, texturePathMap;
	
};


