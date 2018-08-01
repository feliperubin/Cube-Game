//
//  PhysicalObject.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 27/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/PhysicalObject.h"


void PhysicalObject::setTexture(GLuint *texture){this->texture = texture;}
float PhysicalObject::getX(){return xPos;}
float PhysicalObject::getY(){return yPos;}
float PhysicalObject::getZ(){return zPos;}
void PhysicalObject::setX(float xPos){this->xPos = xPos;}
void PhysicalObject::setY(float yPos){this->yPos = yPos;}
void PhysicalObject::setZ(float zPos){this->zPos = zPos;}

void PhysicalObject::nextStage(){}
void PhysicalObject::draw(){}

float PhysicalObject::getNextX(){return xPos;}
float PhysicalObject::getNextY(){return yPos;}
float PhysicalObject::getNextZ(){return zPos;}

//Em relacao a posicao de outro objeto
float PhysicalObject::getMinX(glm::vec3 pos){return xPos-1;}
float PhysicalObject::getMaxX(glm::vec3 pos){return xPos+1;}
float PhysicalObject::getMinY(glm::vec3 pos){return yPos-1;}
float PhysicalObject::getMaxY(glm::vec3 pos){return yPos+1;}
float PhysicalObject::getMinZ(glm::vec3 pos){return zPos-1;}
float PhysicalObject::getMaxZ(glm::vec3 pos){return zPos+1;}

void PhysicalObject::setDestructible(int destructible){this->destructible = destructible;}
int PhysicalObject::getDestructible(){return destructible;}

void  PhysicalObject::setSize(float size){this->size = size;};
float PhysicalObject::getSize(void){return size;};

int PhysicalObject::getSolid(){return solid;}
void PhysicalObject::setSolid(int solid){this->solid = solid;};

float PhysicalObject::heal(float value){
    
    if(destructible){
        if(this->health + value > 0.0f){
            this->health+=value;
            this->dead = 0;
        }
        if(this->health > 100.0f) this->health = 100.0f;
    }
    return this->health;
}
float PhysicalObject::damage(float value){
    
    if(destructible){
        if(this->health - value <= 0.0f){
            this->health = 0.0f;
            this->dead = 1;
        }else{
            this->health-=value;
        }
    }
    
    return health;
    
    
}
int PhysicalObject::isDead(){return dead;}

int PhysicalObject::getTeam(){return this->team;};
void PhysicalObject::setTeam(int team){this->team = team;}

int PhysicalObject::collision(PhysicalObject *po)
{
    float dx = this->getNextX() - po->getNextX();
    float dy = this->getNextY() - po->getNextY();
    float dz = this->getNextZ() - po->getNextZ();
    float distance = sqrtf(dx*dx + dy*dy + dz*dz);
    
    /*
        O meu x,y,z eh o Ponto de Origem EU acho ?
     Tem q Checar  com:
               maxY
                |    maxZ
                |   /
                |  /
                | /
        minX -------- maxX
              / |
             /  |
            /   |
        minZ    |
               minY
     */
    glm::vec3 mypos;
    mypos.x = getNextX();
    mypos.y = getNextY();
    mypos.z = getNextZ();
    int insideX = getMinX(mypos) >= po->getMinX(mypos) && getMaxX(mypos) <= po->getMaxX(mypos);
    int insideZ = getMinZ(mypos) >= po->getMinZ(mypos) && getMaxZ(mypos) <= po->getMaxZ(mypos);
    int insideY = getMinY(mypos) >= po->getMinY(mypos) && getMaxY(mypos) <= po->getMaxY(mypos);
    if(!insideY && !(insideX && insideZ))
        return distance < 3;
    else
        return 0;
}

void PhysicalObject::setDirection(float directionX,float directionY,float directionZ){
    this->directionX = directionX;
    this->directionY = directionY;
    this->directionZ = directionZ;
}
void PhysicalObject::setDirectionX(float directionX){this->directionX = directionX;}
void PhysicalObject::setDirectionY(float directionY){this->directionY = directionY;}
void PhysicalObject::setDirectionZ(float directionZ){this->directionZ = directionZ;}


float PhysicalObject::getHealth(void){return health;}
void PhysicalObject::setHealth(float health){this->health = health;}

double PhysicalObject::getCreationTime(){return this->creationTime;}

