#pragma once
#include "../Physics/Firework.h"
#include "../Physics/FireworksRules.h"
#include "../Model.h"

#include <vector>



class FireworkObject: public Firework, public FireworkRules, public Model
{
public:

//Constructor
    FireworkObject(std::string name, ObjectType objType, GLFWwindow* currWindow);
    ~FireworkObject();

//Property

    /* Store all payload */
    std::vector<FireworkObject*> fireworkPayload;

    /** Holds the set of rules. */
    std::vector<FireworkRules*> rulesList; 
    
    
//Methods
    void initFireworkRules();
    void create(unsigned type, FireworkObject* parent);

    void activate(FireworkObject* parent);
    void applyRules(FireworkObject* firework);

    void deletePayload(FireworkObject* parent);
    bool isPayloadActive();

    void setReady(bool flag);
    bool IsReady();
    

    void updateFireworkObject(float deltaTime);
    void draw();

private:
    FireworkObject* parent;
    bool isReady = false;
    float tick = 0;

};

