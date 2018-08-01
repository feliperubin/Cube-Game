//
//  Square.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 27/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/Square.h"

Square::Square(void)
{
    this->creationTime = global_time;
}
Square::~Square(void){}

void Square::setS(GLfloat s0,GLfloat s1,GLfloat s2,GLfloat s3)
{
    this->s0 = s0;
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
}
void Square::setT(GLfloat t0,GLfloat t1,GLfloat t2,GLfloat t3)
{
    this->t0 = t0;
    this->t1 = t1;
    this->t2 = t2;
    this->t3 = t3;
}
float Square::getWidth(void){return 2*xPos;}
float Square::getHeight(void){return 1;}
float Square::getDepth(void){return 2*zPos;}

float Square::getMinX(glm::vec3 pos){return -xPos;}
float Square::getMaxX(glm::vec3 pos){return xPos;}
float Square::getMinY(glm::vec3 pos){return yPos-1;}
float Square::getMaxY(glm::vec3 pos){return yPos;}
float Square::getMinZ(glm::vec3 pos){return -zPos;}
float Square::getMaxZ(glm::vec3 pos){return zPos;}


void Square::nextStage(void){}

void Square::draw(void)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glBegin(GL_QUADS);
    glTexCoord2f(s0,t0);
    glVertex3f(-xPos, yPos, -zPos);
    glTexCoord2f(s1,t1);
    glVertex3f(-xPos, yPos,  zPos);
    glTexCoord2f(s2,t2);
    glVertex3f( xPos, yPos, zPos);
    glTexCoord2f(s3,t3);
    glVertex3f( xPos, yPos,  -zPos);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    glPopMatrix();

    
    //Debugging Lines X,Y,Z
//    glPushMatrix();
//    //X line RED
//    glColor3f(1, 0, 0);
//    glBegin(GL_QUADS);
//
//    glVertex3f(-xPos, yPos+0.02, -0.5f);
//    glVertex3f(-xPos, yPos+0.02,  0.5f);
//    glVertex3f( xPos, yPos+0.02, 0.5f);
//    glVertex3f( xPos, yPos+0.02,  -0.5f);
//    glEnd();
//
//
//    //Z line BLUE
//    glColor3f(0, 0, 1);
//    glBegin(GL_QUADS);
//    glVertex3f(-0.5, yPos+0.02, -zPos);
//    glVertex3f(-0.5, yPos+0.02,  zPos);
//    glVertex3f( 0.5, yPos+0.02, zPos);
//    glVertex3f( 0.5, yPos+0.02,  -zPos);
//    glEnd();
//    //Y Line GREEN
//    glColor3f(0, 1, 0);
//    glBegin(GL_LINE_STRIP);
//    glVertex3f(0, 0.03f, 0);
//    glVertex3f(0, 30, 0);
//    glEnd();
//
//    glPopMatrix();
    

}
