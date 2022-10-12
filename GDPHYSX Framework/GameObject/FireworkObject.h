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
    /** And the number of rules. */
    const static unsigned ruleCount = 1;

    /** Holds the set of rules. */
    vector<FireworkRules> rules;
    
//Methods
    void initFireworkRules();

    /** Dispatches a firework from the origin. */
    void create(unsigned type, const Firework* parent = NULL);

    /** Dispatches the given number of fireworks from the given parent. */
    void create(unsigned type, unsigned number, const Firework* parent);

    virtual void update();
};

