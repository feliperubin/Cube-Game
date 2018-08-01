//
//  Bullet.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 02/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/Bullet.h"
#include "cgutils.h"
Bullet::Bullet(void)
{
    this->speed = 1.0;
    this->xPos = 0;
    this->yPos = 0;
    this->zPos = 0;
    this->directionX = 0;
    this->directionY = 0;
    this->directionZ = 0;
    this->creationTime = global_time;
}
Bullet::Bullet(float xPos,float yPos,float zPos,float directionX, float directionY,float directionZ)
{
    this->speed = 1.0;
    xPos+=directionX*2;
    zPos+=directionZ*2;
    yPos+=directionY*2;

    this->xPos = xPos;
    this->yPos = yPos;
    this->zPos = zPos;
    this->directionX = directionX;
    this->directionY = directionY;
    this->directionZ = directionZ;
}
Bullet::~Bullet() /* Just initialize variables */
{
}
void Bullet::setX(float xPos){
    this->originalX = xPos;
    this->xPos = xPos;
}
void Bullet::setY(float yPos){
    this->originalY = yPos;
    this->yPos = yPos;
    
}
void Bullet::setZ(float zPos){
    this->originalZ = zPos;
    this->zPos = zPos;
}
float Bullet::getNextX(){return xPos+directionX*speed;}
float Bullet::getNextY(){return yPos+directionY*speed;}
float Bullet::getNextZ(){return zPos+directionZ*speed;}
void Bullet::nextStage(void)
{
    xPos+=directionX*speed;
    yPos+=directionY*speed;
    zPos+=directionZ*speed;
}
void Bullet::draw(void)
{
    
    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos, yPos-1, zPos); //bala
//    glRotatef(bulletRot, 0, 1, 0);
//    glRotatef(bulletRot, 1, 0, 0);
    glRotatef(atan2(directionX,directionZ)*180/acos(-1),0,1,0);
    glScalef(size,size,size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v3);
    glTexCoordPointer(2, GL_FLOAT, 0, t3);
    glNormalPointer(GL_FLOAT, 0, n3);
    glDrawArrays(GL_TRIANGLES, 0, v3Size);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}
int Bullet::collision(PhysicalObject *po){
    int collided = 0;
    glm::vec3 nextpos;
    nextpos.x = getNextX();
    nextpos.y = getNextY();
    nextpos.z = getNextZ();
    
    int insideX = getMinX(nextpos) >= po->getMinX(nextpos) && getMaxX(nextpos) <= po->getMaxX(nextpos);
    int insideZ = getMinZ(nextpos) >= po->getMinZ(nextpos) && getMaxZ(nextpos) <= po->getMaxZ(nextpos);
    int insideY = getMinY(nextpos) >= po->getMinY(nextpos) && getMaxY(nextpos) <= po->getMaxY(nextpos);

    //Debugging
//        printf("Qmin(%f,%f,%f) Qmax(%f,%f,%f)\n",po->getMinX(nextpos),po->getMinY(nextpos),po->getMinZ(nextpos),po->getMaxX(nextpos),po->getMaxY(nextpos),po->getMaxZ(nextpos));

    //Tipo de colisao 2 , talvez nao seja colisao, ja que ta dentro do objeto. Exemplo: Casa.
    if(getMinX(nextpos) < po->getMaxX(nextpos) && getMaxX(nextpos) > po->getMinX(nextpos)){
        if(getMinZ(nextpos) < po->getMaxZ(nextpos) && getMaxZ(nextpos) > po->getMinZ(nextpos)){
            if(getMinY(nextpos) < po->getMaxY(nextpos) && getMaxY(nextpos) > po->getMinY(nextpos)){
                if(insideY) return 2;
                if(insideX&&insideZ) return 1;
                if(!(insideX && insideZ)) return 1;
            }
        }
    }
    return collided;
}

















