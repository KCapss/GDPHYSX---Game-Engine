#include "SwitchManager.h"

SwitchManager* SwitchManager::sharedInstance = NULL;

SwitchManager* SwitchManager::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new SwitchManager();
	}

	return sharedInstance;
}

bool SwitchManager::isShipLightActive()
{
	return this->shipLightActive;
}

void SwitchManager::changeLightSource()
{
	if (this->shipLightActive)
		shipLightActive = false;
	else
		shipLightActive = true;

}

bool SwitchManager::isPerspectiveActive(ActiveCam currCam)
{
	if (currCam == ActiveCam::Perspective)
		return true;
	else
		return false;
}

ActiveCam SwitchManager::changeCam(ActiveCam currCam)
{
	if (currCam == ActiveCam::Perspective) {
		currCam = ActiveCam::Orthographic;
		return currCam;
	}
		
	else if (currCam == ActiveCam::Orthographic) {
		currCam = ActiveCam::Perspective;           
		return currCam; 
	}
		
}

void SwitchManager::updateCurrCam(ActiveCam prevCam)
{
	this->currCam = prevCam;
}

ActiveCam SwitchManager::retrieveCurrCam()
{
	return this->currCam;
}

void SwitchManager::initialize()
{
	this->currCam = ActiveCam::Perspective;
}
