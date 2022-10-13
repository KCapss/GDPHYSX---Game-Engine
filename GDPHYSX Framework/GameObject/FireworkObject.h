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
    vector<FireworkObject*> fireworkPayload;

    /** And the number of rules. */
    const static unsigned ruleCount = 1;

    /** Holds the set of rules. */
    vector<FireworkRules> rulesList; 
    
    //Add static for global checking of the firework Object
    
//Methods
    void initFireworkRules();

    
    /** Dispatches a firework from the origin. */
    void create(unsigned type,  Firework* parent);
    void activate();

    ///** Dispatches the given number of fireworks from the given parent. */
    //void create(unsigned type, unsigned number,  Firework* parent);

    //Activate

    void updateFireworkObject(float deltaTime);
    void draw();

private:
    float tick = 0;

};

