//
//  PhysicalObject.h
//  GLFWCameraView
//
//  Created by Felipe Rubin on 27/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef PhysicalObject_h
#define PhysicalObject_h

#include "globals.h"

class PhysicalObject{
    
public:

    virtual ~PhysicalObject(){}
    
    virtual void nextStage();
    virtual void setTexture(GLuint *texture);
    virtual float getX();
    virtual float getY();
    virtual float getZ();
    virtual float getNextX();
    virtual float getNextY();
    virtual float getNextZ();
    virtual void setX(float xPos);
    virtual void setY(float yPos);
    virtual void setZ(float zPos);
    
    
    virtual void draw();
    virtual int collision(PhysicalObject *po);
    
    virtual float getMinX(glm::vec3 pos);
    virtual float getMaxX(glm::vec3 pos);
    virtual float getMinY(glm::vec3 pos);
    virtual float getMaxY(glm::vec3 pos);
    virtual float getMinZ(glm::vec3 pos);
    virtual float getMaxZ(glm::vec3 pos);

    virtual void setDirection(float directionX,float directionY,float directionZ);
    virtual void setDirectionX(float directionX);
    virtual void setDirectionY(float directionY);
    virtual void setDirectionZ(float directionZ);

    
    /* Is Collision Enabled or Not ?*/
    /* If it is, getSolid() should return 1 */
    virtual int getSolid();
    virtual void setSolid(int solid);
    
    virtual void setDestructible(int destructible);
    virtual int getDestructible();
    
    
    virtual void setSize(float size);
    virtual float getSize(void);
    virtual float getHealth(void);
    virtual void setHealth(float health);
    
    /* Heal this value, return healed health*/
    virtual float heal(float value);
    /* Damage this value, return damaged health*/
    virtual float damage(float value);
    
    // Retorna 1 se esta morto
    // Retorna 0 se esta vivo
    virtual int isDead();
    
    
    virtual double getCreationTime();
    

    virtual int getTeam();
    virtual void setTeam(int team);
protected:
    GLuint *texture;
    float xPos;
    float yPos;
    float zPos;
    float directionX = 0;
    float directionY = 0;
    float directionZ = 0;
    int solid = 0; /* By Default, objects are NOT solid */
    float size = 1;
    float health = 100.0f;
    int destructible = 1;
    int dead = 0;
    double creationTime = 0.0;
    
    int team = -1; //No team
};





#endif /* PhysicalObject_h */
