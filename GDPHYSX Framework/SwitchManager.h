#pragma once
#include "Model.h"

class SwitchManager
{
public:
	static SwitchManager* getInstance();

	//Checking state
	bool isShipLightActive();
	void changeLightSource();

	bool isPerspectiveActive(ActiveCam currCam);
	ActiveCam changeCam(ActiveCam currCam);
	void updateCurrCam(ActiveCam prevCam);
	ActiveCam retrieveCurrCam();

	void initialize();




private:
	// set constructor to private
	SwitchManager() {};

	// set copy constructor to private
	SwitchManager(SwitchManager const&) {}

	// assignment operator is private
	SwitchManager& operator=(SwitchManager const&) {};

	static SwitchManager* sharedInstance;

	bool shipLightActive = true;
	ActiveCam currCam;
};

