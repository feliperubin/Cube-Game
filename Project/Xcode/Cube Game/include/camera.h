//
//  camera.h
//  GLFWCameraView
//
//  Created by Felipe Rubin on 24/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "globals.h"
class Camera
{
public:
    Camera(void);
    ~Camera(void);
     //eye Where am I
    float getX(void);
    float getY(void);
    float getZ(void);


    void setX(float *xPos);
    void setY(float *yPos);
    void setZ(float *zPos);
    
    //Center Which point to look
    float getAtX(void);
    float getAtY(void);
    float getAtZ(void);
    
    //Up Looking from below, above
    float getUpX(void);
    float getUpY(void);
    float getUpZ(void);
    
    void setUpX(float upx);
    void setUpY(float upy);
    void setUpZ(float upz);
    

    
    
    //Sensibility of looking around
    //Speed of camera going forward/backwards/left/right.
    float getSensibility(void);
    void setSensibility(float sensibility);
    void setSpeed(float *speed);
    
    
    
    
    //Aim at some point
    void aim(float x, float y);
    float getHangle(void);
    float getWangle(void);
    
    float getVx();
    float getVy();
    float getVz();
    void setVx(float vx);
    void setVy(float vy);
    void setVz(float vz);
    void setHangle(float hangle);
    void setWangle(float wangle);

    //Do the actual computation to move
    void computeforward(void);
    void computebackwards(void);
    void computeleft(void);
    void computeright(void);
    
    double getCreationTime(void);
    
    void reset(void);

private:
    float *xPos,*yPos,*zPos;
    float vx,vy,vz;
    float wangle, hangle;
    float upx, upy, upz;
    double xprev;
    double yprev;
    float *speed;
    float sensibility;
    double creationTime = 0.0;
//    float xPos;
//    float yPos;
//    float zPos;


};

#endif
