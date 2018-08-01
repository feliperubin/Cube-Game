//
//  Bullet.hpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 02/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h

#include "globals.h"
#include "PhysicalObject.h"
#include "../Models/GunModel.h" //Bullet Model is Inside
class Bullet: public PhysicalObject{
public:
    Bullet(void);
    Bullet(float xPos,float yPos,float zPos,float directionX, float directionY,float directionZ);
    ~Bullet(void);
    void nextStage(void);
    void draw(void);
    
    void setX(float xPos);
    void setY(float yPos);
    void setZ(float zPos);
    
    float getNextX();
    float getNextY();
    float getNextZ();
    float getRadius();
    int collision(PhysicalObject *po);
private:
    float originalX = 0;
    float originalY = 0;
    float originalZ = 0;
    float speed = 0.0f;
};


#endif /* Bullet_h */
