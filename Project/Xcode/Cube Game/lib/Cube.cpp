//
//  Cube.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 27/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/Cube.h"
Cube::Cube(void)
{
    this->size = 1.0f;
    this->renabled = 1;
    this->rotAngle = 0.0f;
    this->creationTime = global_time;
}
Cube::~Cube(void){}

void Cube::nextStage(void)
{
    rotAngle++;
    if(rotAngle == 360) rotAngle = 0;
}
float Cube::getWidth(void){return 3;}
float Cube::getHeight(void){return 3;}
float Cube::getDepth(void){return 3;}

float Cube::getMinX(glm::vec3 pos){return (xPos-1)*size;}
float Cube::getMaxX(glm::vec3 pos){return (xPos+1)*size;}
float Cube::getMinY(glm::vec3 pos){return (yPos-1)*size;}
float Cube::getMaxY(glm::vec3 pos){return (yPos+1)*size;}
float Cube::getMinZ(glm::vec3 pos){return (zPos-1)*size;}
float Cube::getMaxZ(glm::vec3 pos){return (zPos+1)*size;}

//void Cube::setSize(float size){this->size = size;}
//float Cube::getSize(void){return size;}
void Cube::rotateEnabled(int renabled){this->renabled = renabled;}
void Cube::draw(void)
{
    
    //
    /*
        if(!m_shader.isLinked()) return -1
     m_shader.bind()
     m_vao.bind()
     m_shaderProgram.setUniformValue("MVP",m_porjection)
     glDrawArrays(..)
     m_shaderProgram.release();
     */
    
    ///
    
    if(destructible){
        glPushMatrix();
        glTranslatef(xPos, yPos+2, zPos);
        if(this->renabled)
            glRotatef(rotAngle, 0.0, 1.0, 0.0);
        glColor3f(1,0,0);
        glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f,0.2f,0.0f);
        glVertex3f(health/100, 0.2f, 0);
        glVertex3f(health/100, 0.0f, 0);
        glEnd();
        glColor3f(1,1,1);
        glPopMatrix();
    }


    
    
    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos, yPos, zPos);
    if(this->renabled)
        glRotatef(rotAngle, 0.0, 1.0, 0.0);
    glScalef(size, size, size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);    
    glVertexPointer(3, GL_FLOAT, 0,&vCube[0]);
    glTexCoordPointer(3,GL_FLOAT,0,&tCube[0]);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

