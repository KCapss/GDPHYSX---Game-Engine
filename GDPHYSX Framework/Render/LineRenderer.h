#pragma once
#include "../Model.h"
class LineRenderer 
    //: public Model
{
    /*Parameters needed: 
    if Inhereting the Model Class
    1) Name
    2) ObjType
    3) Window

    //Main Paratmers
    1) vec3 Side One
    2) vec3 Side Two


    */
public:
    LineRenderer(glm::vec3 P1, glm::vec3 P2);

    void updatePos(glm::vec3 P1, glm::vec3 P2);
    void draw();


protected:




private:
    glm::vec3 P1;
    glm::vec3 P2;
};

