
//
//  Safezone.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 16/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/Safezone.h"
Safezone::Safezone(void)
{
    this->size = 1.0f;
    /* Bleu de France */
    this->color = glm::vec4(0.27,0.59,0.96,0.3);
    this->min.x = 90;this->min.y = 0;this->min.z = 0;
    this->max.x = 90;this->max.y = 100;this->max.z = 10;
    this->team = 0; //Default Team blue
    //Default position
    this->xPos = 0;
    this->yPos = 0;
    this->zPos = 0;
    this->creationTime = global_time;
}
Safezone::~Safezone(void){}

void Safezone::nextStage(void){}
float Safezone::getMinX(glm::vec3 pos){return (xPos-min.x)*size;}
float Safezone::getMaxX(glm::vec3 pos){return (xPos+max.x)*size;}
float Safezone::getMinY(glm::vec3 pos){return (yPos-min.y)*size;}
float Safezone::getMaxY(glm::vec3 pos){return (yPos+max.y)*size;}
float Safezone::getMinZ(glm::vec3 pos){return (zPos-min.z)*size;}
float Safezone::getMaxZ(glm::vec3 pos){return (zPos+max.z)*size;}
void Safezone::setMax(glm::vec3 max){this->max = max;}
void Safezone::setMin(glm::vec3 min){this->min = min;}
void Safezone::setColor(glm::vec4 color){this->color = color;}
void Safezone::setTeam(int team){this->team = team;}
int Safezone::getTeam(){return this->team;}
void Safezone::draw(void)
{
//    glPushMatrix();
//    glTranslatef(xPos, yPos+2, zPos);
//    
//    glColor3f(1,0,0);
//    glBegin(GL_QUADS);
//    glVertex3f(0.0f, 0.0f, 0.0f);
//    glVertex3f(0.0f,0.2f,0.0f);
//    glVertex3f(health/100, 0.2f, 0);
//    glVertex3f(health/100, 0.0f, 0);
//    glEnd();
//    glColor3f(1,1,1);
//    glPopMatrix();

    glPushMatrix();
    glTranslatef(xPos, yPos, zPos);
    glEnable(GL_BLEND);
    glColor4f(color.x, color.y, color.z, color.w);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glVertex3f(-90,0,0);
    glVertex3f(-90, 100, 0);
    glVertex3f(90, 100, 0);
    glVertex3f(90, 0, 0);
    glEnd();
    glColor3f(1,1,1);
    glDisable(GL_BLEND);
    glPopMatrix();

}

