//
//  Safezone.hpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 16/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Safezone_h
#define Safezone_h

#include "globals.h"
#include "PhysicalObject.h"
class Safezone: public PhysicalObject{
public:
    Safezone(void);
    ~Safezone(void);
    void nextStage(void);
    void draw(void);
    
    float getMinX(glm::vec3 pos);
    float getMaxX(glm::vec3 pos);
    float getMinY(glm::vec3 pos);
    float getMaxY(glm::vec3 pos);
    float getMinZ(glm::vec3 pos);
    float getMaxZ(glm::vec3 pos);
    void setMax(glm::vec3 min);
    void setMin(glm::vec3 max);
    void setColor(glm::vec4 color);
    int getTeam();
    void setTeam(int team);
private:
    glm::vec3 min;
    glm::vec3 max;
    glm::vec4 color;
    int team;
};

#endif /* Safezone_h */
