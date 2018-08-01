//
//  Cube.h
//  GLFWCameraView
//
//  Created by Felipe Rubin on 27/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Cube_h
#define Cube_h
#include "globals.h"
#include "PhysicalObject.h"
#include "../Models/CubeModel.h"
class Cube: public PhysicalObject{
public:
    Cube(void);
    ~Cube(void);
    void nextStage(void);
    void draw(void);
    float getWidth(void);
    float getHeight(void);
    float getDepth(void);
    
    float getMinX(glm::vec3 pos);
    float getMaxX(glm::vec3 pos);
    float getMinY(glm::vec3 pos);
    float getMaxY(glm::vec3 pos);
    float getMinZ(glm::vec3 pos);
    float getMaxZ(glm::vec3 pos);
    
    void rotateEnabled(int renabled);
    
private:
    float rotAngle;
    
    int renabled;
};

#endif /* Cube_h */
