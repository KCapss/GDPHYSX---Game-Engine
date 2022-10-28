#pragma once
#include "Space.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Base Model
#include "Model.h"
#include "Skybox.h"
#include "Player.h"

//Physic Base Model
#include "GameObject/ParticleObject.h"
#include "GameObject/BallisticContainer.h"
#include "GameObject/BallisticObject.h"
#include "GameObject/FireworkObject.h"

//Force Generator
#include "GameObject/AnchorSpringObject.h"
#include "GameObject/SpringObject.h"
#include "GameObject/BungeeObject.h"

#include "Light.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"

#include <string>
#include <iostream>

class Space
{
public: 
	//Constructor
	GLFWwindow* window;
	Space(int length, int width);
	bool initializeWindow();

	void initializeObj();

	void update(float deltaTime);
	void draw();
	void deleteBuffer();

	//Debri Handler
	void debriInitialize();
	void debriRetrieveSource();
	void debriSetup();
	void drawDebri();
	void deleteDebri();

	//projectile Handler
	void projectileInit(int size); //including the source
	

	// key callback
	void input();


private:
	//Interface:
	Skybox* skybox;

	//Model for the physics base model;
	ParticleObject *planet;
	BallisticObject* projectile;
	FireworkObject* fireworksObject;
	BallisticContainer* projectileContainer;

	//ForceGenerator
	ParticleObject* refParticle;
	AnchorSpringObject* ASpringObject;
	SpringObject* springObject;
	BungeeObject* bungeeObject;

	//
	


	//Debri
	Model* tower;
	Model* generators;
	Model* spaceRock;
	Model* statue;
	Model* statue2;
	Player* player;

	//External Src
	Light* lightSrc;
	PerspectiveCamera* mainCam;
	OrthographicCamera* alterCam;

	int lengthDim = 0, widthDim = 0; //set default

	// Stores shot type
	ShotTypes shotType;
	

};

