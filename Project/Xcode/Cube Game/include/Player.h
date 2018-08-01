//
//  Player.h
//  GLFWCameraView
//
//  Created by Felipe Rubin on 27/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "globals.h"
#include "../include/PhysicalObject.h"
#include "../include/camera.h"
#include "../include/Cube.h"

#include "../Models/GunModel.h"

#include "../include/Safezone.h"
class Player: public PhysicalObject{
public:
    
    Player(void);
    ~Player(void);

    Camera* getCamera(void);
    void setCamera(Camera cam);
    void resetCamera(void);
    void draw();
    void nextStage();
    float getX();
    float getY();
    float getZ();
    void setX(float xPos);
    void setY(float yPos);
    void setZ(float zPos);
    float getNextX();
    float getNextY();
    float getNextZ();

    
    void setTexture(GLuint *texture);
    
    int collision(PhysicalObject *po);
    int safezonecollision(Safezone *po);

    float getMinX(glm::vec3 pos);
    float getMaxX(glm::vec3 pos);
    float getMinY(glm::vec3 pos);
    float getMaxY(glm::vec3 pos);
    float getMinZ(glm::vec3 pos);
    float getMaxZ(glm::vec3 pos);
    
    void move();

    
    /* Interface */
    int getViewportX();
    int getViewportY();
    void setViewportX(int viewportX);
    void setViewportY(int viewportY);
    int getDevice(void);
    void setDevice(int device);
    
    
    /* Movement */
    void forward(int state);
    void backwards(int state);
    void left(int state);
    void right(int state);
    void jump(int state);
    void aim(float x, float y);
    
    void enableGravity();
    void disableGravity();
    
    void setSpeed(float speed);
    
    float getYHigh();
    float getYLow();
    void setYHigh(float yhigh);
    void setYLow(float ylow);

    float getRadius();
    
    float getAtX();
    float getAtY();
    float getAtZ();
    float getUpX();
    float getUpY();
    float getUpZ();
    
    void setWeaponTextures(GLuint *bulletTexture,GLuint *gunTexture);
    
    
    /* Animations */
    int shootAnimation(void);/* Shooting */
    int deathAnimation(int time, int step);
    int deathAnimationStep(void);
    
    
    
    std::vector<double>* getDeaths();
    
private:
    GLuint *bulletTexture,*gunTexture;
    Camera cam;
    Cube cub;
    std::vector<double> deaths;
    
    float upGunAnimation, releaseGunAnimation;
    int deathTimer,deathTimerStep;
    

    
    //View Config
    int viewportX;
    int viewportY;
    int viewportHeight;
    int viewportWidth;
    int device;
    
    float nextX,nextUpx,nextAtx;
    float nextY,nextUpy,nextAty;
    float nextZ,nextUpz,nextAtz;
    
    float upx, atx;
    float upy, aty;
    float upz, atz;
    
    float speed;
    int fwenabled,bwenabled,ltenabled,rtenabled,genabled;
    
    //Begin Aim Test
    int aimenabled;
    float xAim;
    float yAim;
    //End Aim Testd
    double jumpbegin; //Time Jump actually started
    int jumpup;
    double lasttime;
    float yspeed;
    
    void computeJump(void);
    void gravity(void);
    float yhigh,ylow; // Ceiling yHigh, Floor Ylow
    float nextyhigh,nextylow; // Next Ceiling yHigh, Floor Ylow

    
};

#endif /* Player_h */
