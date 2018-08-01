//
//  Column.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 02/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/Column.h"

Column::Column(){
    this->creationTime = global_time;
}
Column::~Column(){}
float Column::getMinX(glm::vec3 pos){
    return xPos - (fabsf(maxX - minX)*size/2);
}
float Column::getMaxX(glm::vec3 pos){
    return xPos + (fabsf(maxX - minX)*size/2);
}
float Column::getMinY(glm::vec3 pos){
    return yPos;
}
float Column::getMaxY(glm::vec3 pos){
    return ((fabsf(maxY - minY)*size) -yPos);
}
float Column::getMinZ(glm::vec3 pos){
    return zPos - (fabsf(maxZ - minZ)*size)/2;
}
float Column::getMaxZ(glm::vec3 pos){
    return zPos + (fabsf(maxZ - minZ)*size)/2;
}

void Column::nextStage(void)
{
//    zPos+=0.1;
}
void Column::draw(void)
{

    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos, yPos, zPos);
    glScalef(size,size,size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &vColumn[0]);
    glTexCoordPointer(3, GL_FLOAT, 0, &tColumn[0]);
    glDrawArrays(GL_TRIANGLES, 0, vColumnSize);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


















