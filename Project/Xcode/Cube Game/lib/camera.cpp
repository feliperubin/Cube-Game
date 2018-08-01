//
//  camera.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 24/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/camera.h"
/*
    This Camera Implementation is based on
    http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
 */
Camera::Camera(void)
{
    upx = 0.0f;
    upy = 1.1f;
    upz = 0.0f;
    vx = 0.0f;
    vy = 0.0f;
    vz = -1.0f;
    hangle = NULL;
    wangle = NULL;
    xprev = NULL;
    yprev = NULL;
    sensibility = 0.01; //0.01 x , 0.005 y
    this->creationTime = global_time;
}
//Reta a camera
void Camera::reset(void)
{
    upx = 0.0f;
    upy = 1.1f;
    upz = 0.0f;
    vx = 0.0f;
    vy = 0.0f;
    vz = -1.0f;
    hangle = NULL;
    wangle = NULL;
    xprev = NULL;
    yprev = NULL;
    sensibility = 0.01; //0.01 x , 0.005 y
}
Camera::~Camera(void){}

//Center Which point to look
float Camera::getAtX(void){return *xPos+vx;}
float Camera::getAtY(void){return *yPos+vy;}
float Camera::getAtZ(void){return *zPos+vz;}
//Up Looking from below, above ..
float Camera::getUpX(void){return upx;}
float Camera::getUpY(void){return upy;}
float Camera::getUpZ(void){return upz;}

float Camera::getSensibility(void){return sensibility;}
void Camera::setSensibility(float sensibility){this->sensibility = sensibility;}
void Camera::setSpeed(float *speed){this->speed = speed;}

//eye Where am I
float Camera::getX(void){return *xPos;}
float Camera::getY(void){return *yPos;}
float Camera::getZ(void){return *zPos;}

void Camera::setX(float *xPos){this->xPos = xPos;}
void Camera::setY(float *yPos){this->yPos = yPos;}
void Camera::setZ(float *zPos){this->zPos = zPos;}

void Camera::setUpX(float upx){this->upx = upx;}
void Camera::setUpY(float upy){this->upy = upy;}
void Camera::setUpZ(float upz){this->upz = upz;}

float Camera::getVx(){return vx;}
float Camera::getVy(){return vy;}
float Camera::getVz(){return vz;}

void Camera::setVx(float vx){this->vx = vx;}
void Camera::setVy(float vy){this->vy = vy;}
void Camera::setVz(float vz){this->vz = vz;}
void Camera::setHangle(float hangle){this->hangle = hangle;}
void Camera::setWangle(float wangle){this->wangle = wangle;}

double Camera::getCreationTime(){return this->creationTime;}

void Camera::computeforward()
{
    *xPos+= vx * *speed;
    *zPos+= vz * *speed;
}
void Camera::computebackwards()
{
    *xPos+= vx * -*speed;
    *zPos+= vz * -*speed;
    
}
void Camera::computeleft()
{
    *xPos+= *speed * sin(vz);
    *zPos+= *speed * -sin(vx);
    
}
void Camera::computeright()
{
    *xPos-= *speed * sin(vz);
    *zPos-= *speed * -sin(vx);
}

float Camera::getHangle(){return hangle;}
float Camera::getWangle(){return wangle;}

//Aim at some point
void Camera::aim(float x, float y)
{
    if(xprev == NULL && yprev == NULL){
        xprev = x;
        yprev = y;
    }
    float deltaX = x - xprev;
    float deltaY = y - yprev;
    if(deltaX != 0){
        wangle+= deltaX * sensibility;//0.01 sendo a sensibilidade
        vx = sin(wangle);
        vz = -cos(wangle);
    }
    if(deltaY != 0){
        hangle+= deltaY * sensibility;
        if(hangle > 1) hangle = 1;
        else if (hangle < -1) hangle = -1;
        vy = -sin(hangle);
    }

    xprev = x;
    yprev = y;
}












