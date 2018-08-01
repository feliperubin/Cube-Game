//
//  Bird.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 02/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/Bird.h"

Bird::Bird()
{
    this->size = 1.0f;
    this->birdId = -1;
    this->currentFrame = 0;
    this->prevPos = NULL;
    this->vi = NULL;
    this->creationTime = global_time;
}
Bird::~Bird(){}

//float Bird::getMinX(glm::vec3 pos){
////    printf("MinX = %f\n",xPos - (fabsf(bmaxX - bminX)*size/2));
//    return xPos - (fabsf(bmaxX - bminX)*size/2);
//}
//float Bird::getMaxX(glm::vec3 pos){
////    printf("MaxX = %f\n",xPos + (fabsf(bmaxX - bminX)*size/2));
//    return xPos + (fabsf(bmaxX - bminX)*size/2);
//}
//float Bird::getMinY(glm::vec3 pos){
////    return bminY-yPos;
//    return yPos;
//}
//float Bird::getMaxY(glm::vec3 pos){
//    return ((fabsf(bmaxY - bminY)*size)-yPos);
//}
//float Bird::getMinZ(glm::vec3 pos){
//    return zPos - (fabsf(bmaxZ - bminZ)*size)/2;
//}
//float Bird::getMaxZ(glm::vec3 pos){
//    return zPos + (fabsf(bmaxZ - bminZ)*size)/2;
//}


void Bird::setTimeSeries(VideoInfo *vi, int birdId)
{
    this->vi = vi;
    this->birdId = birdId;
    prevPos = NULL;
    
}



void Bird::nextStage(void)
{

    /*Animation*/
    if(angle == 0) up = 0;
    else if(angle == 90) up = 1;
    if(up){
        angle--;
    }else{
        angle++;
    }
    if(this->birdId == -1){
        zPos+=0.1;
        return;
    }
    
    /* Next Position*/
    if(currentFrame >= vi->length) currentFrame = 0; //Recomeca
    Person* birdPerson = &vi->frames[currentFrame].person[birdId];
    if(birdPerson->valid){
        xPos = ((birdPerson->point.x*vi->pxm));
        
        xPos = -100.0f + ((xPos - vi->minpoint.x * vi->pxm) * (200.0f)/(vi->maxpoint.x*vi->pxm - vi->minpoint.x *vi->pxm));
        
        zPos = ((birdPerson->point.y*vi->pxm));
        zPos = -100.0f + ((zPos - vi->minpoint.y * vi->pxm) * (200.0f)/(vi->maxpoint.y*vi->pxm - vi->minpoint.y *vi->pxm));
        if(prevPos == NULL){
            Point auxpoint = Point{.x = xPos, .y = zPos};
            prevPos = &auxpoint;
            
        };

        yPos = (magnitude(birdPerson->point) * magnitude(*prevPos) * cosvector(birdPerson->point,*prevPos));
        *prevPos = Point{.x = xPos, .y = zPos};
    }
    currentFrame++;
    
}
void Bird::draw(void)
{
    

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(xPos-0.005*angle, yPos, zPos);
    glScalef(size,size,size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glRotatef(angle,0.2,0,-1);

    /* Draw Left Wing */
    glVertexPointer(3, GL_FLOAT, 0, &vLeftWing[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &tLeftWing[0]);
    glDrawArrays(GL_QUADS, 0, vLeftWingSize);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(xPos+0.005*angle, yPos, zPos);
    glScalef(size,size,size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glRotatef(angle,0.2,0,1);
    /* Draw Right Wing*/
    glVertexPointer(3, GL_FLOAT, 0, &vRightWing[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &tRightWing[0]);
    glDrawArrays(GL_QUADS, 0, vRightWingSize);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    

    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos, yPos+angle*0.001, zPos);
    glScalef(size,size,size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    /* Draw Body*/
    glVertexPointer(3, GL_FLOAT, 0, &vBody[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &tBody[0]);
    glDrawArrays(GL_QUADS, 0, vBodySize);
    /* Draw Tail */
    glVertexPointer(3, GL_FLOAT, 0, &vTail[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &tTail[0]);
    glDrawArrays(GL_TRIANGLES, 0, vTailSize);

    /* Draw Beak */
    glVertexPointer(3, GL_FLOAT, 0, &vBeak[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &tBeak[0]);
    glDrawArrays(GL_TRIANGLES, 0, vBeakSize);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    
    
        if(destructible){
            glPushMatrix();
            glTranslatef(xPos, yPos+2+angle*0.001, zPos);
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

}


















