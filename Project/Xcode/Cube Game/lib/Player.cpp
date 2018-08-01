//
//  Player.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 27/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/Player.h"
Player::Player(void){
    
    this->device = 0;
    this->viewportX = 0;
    this->viewportY = 0;
    this->health = 100.0f;
    this->xPos = 0.0f;
    this->yPos = 10.0f;
    this->zPos = 5.0f;
    this->nextX = 0.0f;
    this->nextY = 10.0f;
    this->nextZ = 5.0f;
    this->nextylow = 0.0f;
    this->nextyhigh = 100.0f;
    this->atx = 0;
    this->aty = 0;
    this->atz = 0;
    this->upx = 0;
    this->upy = 0;
    this->upz = 0;
    this->cam.setX(&nextX);
    this->cam.setY(&nextY);
    this->cam.setZ(&nextZ);
    this->speed = 0.1f;
    this->cam.setSpeed(&speed);
    this->lasttime = global_time;
    this->yspeed = 1.0f;
    this->fwenabled = 0;
    this->bwenabled = 0;
    this->ltenabled = 0;
    this->rtenabled = 0;
    this->genabled = 1;
    this->jumpup = 0;
    this->jumpbegin = 0;
    this->ylow = 0.0f;
    this->yhigh = 100.0f;
    //test
    this->aimenabled = 0;
    this->xAim = 0;
    this->yAim = 0;
    
    this->solid = 1;
    
    this->upGunAnimation = -1;
    this->releaseGunAnimation = 0;
    this->dead = 0;
    this->cub.setDestructible(0);
    this->creationTime = global_time;
    
    
    this->deathTimer = 0;
    this->deathTimerStep = 0;
    this->team = 0;
};
Player::~Player(void){};
Camera* Player::getCamera(void){return &cam;}
void Player::setCamera(Camera cam){
    this->cam = cam;
    this->cam.setX(&nextX);
    this->cam.setY(&nextY);
    this->cam.setZ(&nextZ);
    this->cam.setSpeed(&speed);
}

void Player::resetCamera()
{
    
    
    this->atx = 0;
    this->aty = 0;
    this->atz = 0;
    this->upx = 0;
//    this->upy = 0; //Causa um bug no fading
    this->upz = 0;

    this->speed = 0.1f;
    this->lasttime = global_time;
    this->yspeed = 1.0f;
    this->fwenabled = 0;
    this->bwenabled = 0;
    this->ltenabled = 0;
    this->rtenabled = 0;
    this->genabled = 1;
    this->jumpup = 0;
    this->jumpbegin = 0;
    this->ylow = 0.0f;
    this->yhigh = 100.0f;
    this->aimenabled = 0;
    this->xAim = 0;
    this->yAim = 0;
    this->upGunAnimation = -1;
    this->releaseGunAnimation = 0;
    this->cam.reset();
    this->cam.setX(&nextX);
    this->cam.setY(&nextY);
    this->cam.setZ(&nextZ);
    this->cam.setSpeed(&speed);
}

void Player::forward(int state){fwenabled = state;}
void Player::backwards(int state){bwenabled = state;}
void Player::left(int state){ltenabled = state;}
void Player::right(int state){rtenabled = state;}

void Player::aim(float x, float y){
    if(aimenabled) return;
    xAim = x;
    yAim = y;
    aimenabled = 1;
}

float Player::getX(){return xPos;}
float Player::getY(){return yPos;}
float Player::getZ(){return zPos;}
float Player::getAtX(){return atx;}
float Player::getAtY(){return aty;}
float Player::getAtZ(){return atz;}
float Player::getUpX(){return upx;}
float Player::getUpY(){return upy;}
float Player::getUpZ(){return upz;}

void Player::setX(float xPos){this->nextX = xPos;this->xPos = xPos;}
void Player::setY(float yPos){this->nextY = yPos;this->yPos = yPos;}
void Player::setZ(float zPos){this->nextZ = zPos;this->zPos = zPos;}

void Player::setTexture(GLuint *texture){cub.setTexture(texture);}
void Player::setSpeed(float speed){this->speed = speed;}

float Player::getNextX(){return nextX;}
float Player::getNextY(){return nextY;}
float Player::getNextZ(){return nextZ;}


float Player::getMinX(glm::vec3 pos){return getNextX()-1;}
float Player::getMaxX(glm::vec3 pos){return getNextX()+1;}
float Player::getMinY(glm::vec3 pos){return getNextY()-1 <= ylow ? ylow : getNextY()-1;}//Tenho Tamanho 1 agora max-min = 1
float Player::getMaxY(glm::vec3 pos){return getNextY()+1 >= yhigh ? yhigh : getNextY()+1;}//
float Player::getMinZ(glm::vec3 pos){return getNextZ()-1;}
float Player::getMaxZ(glm::vec3 pos){return getNextZ()+1;}

float Player::getRadius(){return 1;}

std::vector<double>* Player::getDeaths(){return &deaths;}

void Player::move()
{
    
    ylow = nextylow;
    xPos = nextX;
    yPos = nextY;
    zPos = nextZ;
    atx = cam.getAtX();
    aty = cam.getAtY();
    atz = cam.getAtZ();
    upx = cam.getUpX();
    upy = cam.getUpY();
    upz = cam.getUpZ();
    if(aimenabled){
        cam.aim(xAim, yAim);
        aimenabled = 0;
    }
    if(fwenabled) cam.computeforward();
    if(bwenabled) cam.computebackwards();
    if(ltenabled) cam.computeleft();
    if(rtenabled) cam.computeright();
    if(genabled) gravity(); // e esse  ?
    nextylow = -10000.0f;
    nextyhigh = 10000.0f;
    
    
    if(upGunAnimation == 1){
        releaseGunAnimation+=0.05;
        if(releaseGunAnimation >= 0.25) upGunAnimation--;
    }else if(upGunAnimation == 0){
        releaseGunAnimation-=0.05;
        if(releaseGunAnimation <= 0) upGunAnimation--;
    }


}


void Player::nextStage(){}
///
//Relacionado a animacoes de tiro, etc..
void Player::setWeaponTextures(GLuint *bulletTexture,GLuint *gunTexture){this->bulletTexture = bulletTexture;this->gunTexture = gunTexture;}

//Retorna 1 se pode comecar a animacao.
//Retorna 0 se ja tem uma em andamento
int Player::shootAnimation(void){
//    if(releaseGunAnimation > )
    if(upGunAnimation == -1){
        upGunAnimation = 1;
        return 1;
    }
    return 0;
}

int Player::deathAnimation(int time,int step){
    if(deathTimer == 0.00){
        this->deathTimerStep = step;
        this->deathTimer = time;
        return 1;
    }
    return 0;
}
int Player::deathAnimationStep(void){
    this->deathTimer = this->deathTimer - this->deathTimerStep;
    if(this->deathTimer < 0) this->deathTimer = 0;
    return this->deathTimer;
}


///
void Player::draw()
{
//    printf("V(%f,%f,%f)\n",cam.getVx(),cam.getVy(),cam.getVz());
    if(health < 100)
        glColor3f((health*0.01)*1,0,0);
    cub.setX(xPos);
    cub.setY(yPos);
    cub.setZ(zPos);
    glPushMatrix();
//    glRotatef(atan2(cam.getVx(),cam.getVz())*180/acos(-1),0,1,0);
//    glRotatef(180,0,1,0);
    cub.draw();
    glPopMatrix();
    
    
    /* Debugging Collision Vectors*/

//    glPushMatrix();
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    glm::vec3 mypos;
//    glBegin(GL_QUADS);
//        glColor4f(1, 0, 0,0.5);
//        glVertex3f(getMinX(mypos), getMinY(mypos), getMinZ(mypos));
//        glVertex3f(getMinX(mypos), getMinY(mypos), getMaxZ(mypos));
//        glVertex3f(getMaxX(mypos), getMinY(mypos), getMaxZ(mypos));
//        glVertex3f(getMaxX(mypos), getMinY(mypos), getMinZ(mypos));
//        glColor4f(0, 1, 0,0.5);
//        glVertex3f(getMinX(mypos), getMaxY(mypos), getMinZ(mypos));
//        glVertex3f(getMinX(mypos), getMaxY(mypos), getMaxZ(mypos));
//        glVertex3f(getMaxX(mypos), getMaxY(mypos), getMaxZ(mypos));
//        glVertex3f(getMaxX(mypos), getMaxY(mypos), getMinZ(mypos));
//
//        glColor4f(0, 0, 1,0.5);
//        glVertex3f(getMinX(mypos), ylow, getMinZ(mypos));
//        glVertex3f(getMinX(mypos), ylow, getMaxZ(mypos));
//        glVertex3f(getMaxX(mypos), ylow, getMaxZ(mypos));
//        glVertex3f(getMaxX(mypos), ylow, getMinZ(mypos));
//
//    glColor4f(1,1,1,1);
//    glEnd();
//    glDisable(GL_BLEND);
//    glPopMatrix();

    
    //Abaixo desenha a arma
    static float bulletRot = 0;

    
    glPushMatrix();
    glColor3f(1,1, 1);
//    glTranslatef(xPos-1, yPos, zPos-1); //O cano em q a bala fica quando a arma ta carregada
    glTranslatef(xPos-1+releaseGunAnimation*cam.getVx(), yPos, zPos-1+releaseGunAnimation*cam.getVz());
    glRotatef(180-atan2(cam.getVx(),cam.getVz())*180/acos(-1),0,1,0);
    glScalef(size*0.1,size*0.1,size*0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *bulletTexture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v0);
    glTexCoordPointer(2, GL_FLOAT, 0, t0);
    glNormalPointer(GL_FLOAT, 0, n0);
    glDrawArrays(GL_TRIANGLES, 0, v0Size);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos-1, yPos, zPos-1); //uma parte q n sei qq faz
    glRotatef(180-atan2(cam.getVx(),cam.getVz())*180/acos(-1),0,1,0);
    glScalef(size*0.1,size*0.1,size*0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *bulletTexture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v1);
    glTexCoordPointer(2, GL_FLOAT, 0, t1);
    glNormalPointer(GL_FLOAT, 0, n1);
    glDrawArrays(GL_TRIANGLES, 0, v1Size);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,1, 1);
//    glTranslatef(xPos-1, yPos, zPos-1); //negocio q tu puxa p/ carregar
    glTranslatef(xPos-1+releaseGunAnimation*cam.getVx(), yPos, zPos-1+releaseGunAnimation*cam.getVz());
    glRotatef(180-atan2(cam.getVx(),cam.getVz())*180/acos(-1),0,1,0);
    glScalef(size*0.1,size*0.1,size*0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *gunTexture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v2);
    glTexCoordPointer(2, GL_FLOAT, 0, t2);
    glNormalPointer(GL_FLOAT, 0, n2);
    glDrawArrays(GL_TRIANGLES, 0, v2Size);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    

    glPushMatrix();
    glColor3f(1,1, 1);
    
    glTranslatef(xPos-1, yPos, zPos-1); //bala
    glRotatef(180-atan2(cam.getVx(),cam.getVz())*180/acos(-1),0,1,0);
    glRotatef(bulletRot, 0, 1, 0);
    glRotatef(bulletRot, 1, 0, 0);
    glScalef(size*0.1,size*0.1,size*0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *bulletTexture);
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
    
    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos-1, yPos, zPos-1); //corpo
    glRotatef(180-atan2(cam.getVx(),cam.getVz())*180/acos(-1),0,1,0);
    glScalef(size*0.1,size*0.1,size*0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *gunTexture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v4);
    glTexCoordPointer(2, GL_FLOAT, 0, t4);
    glNormalPointer(GL_FLOAT, 0, n4);
    glDrawArrays(GL_TRIANGLES, 0, v4Size);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos-1+releaseGunAnimation*cam.getVx(), yPos, zPos-1+releaseGunAnimation*cam.getVz());
//    glTranslatef(xPos, yPos, zPos+release);
    //    glTranslatef(xPos,yPos,zPos); //negocio q vai pra tras e pra frente
    glRotatef(180-atan2(cam.getVx(),cam.getVz())*180/acos(-1),0,1,0);
    glScalef(size*0.1,size*0.1,size*0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *gunTexture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, v5);
    glTexCoordPointer(2, GL_FLOAT, 0, t5);
    glNormalPointer(GL_FLOAT, 0, n5);
    glDrawArrays(GL_TRIANGLES, 0, v5Size);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,1, 1);
   glTranslatef(xPos-1, yPos, zPos-1); //Cartucho
    glRotatef(180-atan2(cam.getVx(),cam.getVz())*180/acos(-1),0,1,0);
    glScalef(size*0.1,size*0.1,size*0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *bulletTexture);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, &v6[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &t6[0]);
    glNormalPointer(GL_FLOAT, 0, &n6[0]);
    glDrawArrays(GL_TRIANGLES, 0, v6Size);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    
    
    


    
    
    
}
/*
    yLow = Menor y q pode o ylow pode chegar
    miny = a posicao y dos "pes", parte + baixa do player
    maxy = a posicao y dos "olhos", parte + alta do player
 */

int Player::collision(PhysicalObject *po)
{
    int collided = 0;
    /*
        Funcionamento da Colisao:
        Os InsideX,Y,Z verificam se eu vou bater em uma das faces,
        Tanto de dentro pra fora quanto de fora p/ dentro
     */
    glm::vec3 mypos;
    mypos.x = getNextX();
    mypos.y = getNextY();
    mypos.z = getNextZ();
    /* Testar se eu ja nao to dentro, se estiver, nao eh colisao! */
    
    
    
    
    
    
    int outsideX = getMinX(mypos) < po->getMaxX(mypos) && getMaxX(mypos) > po->getMinX(mypos);
    
    //Debugging
//    printf("Qmin(%f,%f,%f) Qmax(%f,%f,%f)\n",po->getMinX(mypos),po->getMinY(mypos),po->getMinZ(mypos),po->getMaxX(mypos),po->getMaxY(mypos),po->getMaxZ(mypos));

    if(outsideX){
        int outsideZ = getMinZ(mypos) < po->getMaxZ(mypos) && getMaxZ(mypos) > po->getMinZ(mypos);

        if(outsideZ){
            int outsideY = getMinY(mypos) < po->getMaxY(mypos) && getMaxY(mypos) > po->getMinY(mypos);
            int insideY = getMinY(mypos) >= po->getMinY(mypos) && getMaxY(mypos) <= po->getMaxY(mypos);

            if(outsideY){
                int insideX = getMinX(mypos) >= po->getMinX(mypos) && getMaxX(mypos) <= po->getMaxX(mypos);
                int insideZ = getMinZ(mypos) >= po->getMinZ(mypos) && getMaxZ(mypos) <= po->getMaxZ(mypos);

                if(!(insideX && insideZ)){
                    int resolveX = !(xPos-1 < po->getMaxX(mypos) && xPos+1 > po->getMinX(mypos));
                    int resolveY = !(yPos-1 <= ylow ? ylow : yPos-1 < po->getMaxY(mypos) && yPos+1 >= yhigh ? yhigh : yPos+1 > po->getMinY(mypos));
                    int resolveZ = !(zPos-1 < po->getMaxZ(mypos) && zPos+1 > po->getMinZ(mypos));
                    int resolveInsideX = !(xPos-1 >= po->getMinX(mypos) && xPos+1 <= po->getMaxX(mypos));
                    int resolveInsideZ = !(zPos-1 >= po->getMinZ(mypos) && zPos+1 <= po->getMaxZ(mypos));
                    int resolveInsideY = !(yPos-1 <= ylow ? ylow : yPos-1 >= po->getMinY(mypos) && yPos+1 >= yhigh ? yhigh : yPos+1 <= po->getMaxY(mypos));

                    if(resolveX || (!resolveInsideX && insideZ)){
                        nextX = xPos;
                        nextylow = ylow;
                    }else if(resolveZ || (insideX && !resolveInsideZ)){
                        nextZ = zPos;
                        nextylow = ylow;
                    }else if(resolveY){
                        nextY = yPos;
                    }else{
                        nextX = xPos;
                        nextZ = zPos;
                        nextY = yPos;
                    }
                    nextylow = ylow;
                    collided = 1;
                }else{
                    if(insideY){
//                        printf("Inside\n");
                        if(nextylow <= po->getMinY(mypos)) this->nextylow = po->getMinY(mypos);
                        if(nextyhigh <= po->getMaxY(mypos)) this->nextyhigh = po->getMaxY(mypos);
                        collided = 2;
                    }
                }
            }else if(getMinY(mypos) >= po->getMaxY(mypos)){//TO acima
                if(nextylow <= po->getMaxY(mypos)){
                    this->nextylow = po->getMaxY(mypos);
                }else{}
            }else{// To abaixo
                if(!insideY){
                    if(nextyhigh >= po->getMinY(mypos)) this->nextyhigh = po->getMinY(mypos);
                    collided = 4;
                }

            }
        }
    }
    return collided;
}



int Player::safezonecollision(Safezone *po)
{
    int collided = 0;
    int sameTeam = po->getTeam() == this->team;
    /*
     Funcionamento da Colisao:
     Os InsideX,Y,Z verificam se eu vou bater em uma das faces,
     Tanto de dentro pra fora quanto de fora p/ dentro
     */
    glm::vec3 mypos;
    mypos.x = getNextX();
    mypos.y = getNextY();
    mypos.z = getNextZ();
    /* Testar se eu ja nao to dentro, se estiver, nao eh colisao! */
    int outsideX = getMinX(mypos) < po->getMaxX(mypos) && getMaxX(mypos) > po->getMinX(mypos);

    //Debugging
    //    printf("Qmin(%f,%f,%f) Qmax(%f,%f,%f)\n",po->getMinX(mypos),po->getMinY(mypos),po->getMinZ(mypos),po->getMaxX(mypos),po->getMaxY(mypos),po->getMaxZ(mypos));
    
    if(outsideX){

        int outsideZ = getMinZ(mypos) < po->getMaxZ(mypos) && getMaxZ(mypos) > po->getMinZ(mypos);

        if(outsideZ){
            int outsideY = getMinY(mypos) < po->getMaxY(mypos) && getMaxY(mypos) > po->getMinY(mypos);
            int insideY = getMinY(mypos) >= po->getMinY(mypos) && getMaxY(mypos) <= po->getMaxY(mypos);

            if(outsideY){
                int insideZ = getMinZ(mypos) >= po->getMinZ(mypos) && getMaxZ(mypos) <= po->getMaxZ(mypos);
                int insideX = getMinX(mypos) >= po->getMinX(mypos) && getMaxX(mypos) <= po->getMaxX(mypos);
                if(!(insideX && insideZ) && !sameTeam){
                    int resolveX = !(xPos-1 < po->getMaxX(mypos) && xPos+1 > po->getMinX(mypos));
                    int resolveY = !(yPos-1 <= ylow ? ylow : yPos-1 < po->getMaxY(mypos) && yPos+1 >= yhigh ? yhigh : yPos+1 > po->getMinY(mypos));
                    int resolveZ = !(zPos-1 < po->getMaxZ(mypos) && zPos+1 > po->getMinZ(mypos));
                    int resolveInsideX = !(xPos-1 >= po->getMinX(mypos) && xPos+1 <= po->getMaxX(mypos));
                    int resolveInsideZ = !(zPos-1 >= po->getMinZ(mypos) && zPos+1 <= po->getMaxZ(mypos));
                    int resolveInsideY = !(yPos-1 <= ylow ? ylow : yPos-1 >= po->getMinY(mypos) && yPos+1 >= yhigh ? yhigh : yPos+1 <= po->getMaxY(mypos));

                    if(resolveX || (!resolveInsideX && insideZ)){
                        nextX = xPos;
                        nextylow = ylow;
                    }else if(resolveZ || (insideX && !resolveInsideZ)){
                        nextZ = zPos;
                        nextylow = ylow;
                    }else if(resolveY){
                        nextY = yPos;
                    }else{
                        nextX = xPos;
                        nextZ = zPos;
                        nextY = yPos;
                    }
                    nextylow = ylow;
                    collided = 1;
                }else{
                    if(insideY){
                        if(nextylow <= po->getMinY(mypos)&&!sameTeam) this->nextylow = po->getMinY(mypos);
                        if(nextyhigh <= po->getMaxY(mypos)&&!sameTeam) this->nextyhigh = po->getMaxY(mypos);
//                        printf("Inside %f\n",this->nextZ);
                        if(!sameTeam)
                            collided = 2;
                        else
                            this->heal(0.1f);
                    }else{}
                }
            }else if(getMinY(mypos) >= po->getMaxY(mypos)){//TO acima
                if(nextylow <= po->getMaxY(mypos)&&!sameTeam){
                    this->nextylow = po->getMaxY(mypos);
                    //                    collided = 3;
                }else{}
            }else{// To abaixo
                if(!insideY&&!sameTeam){
                    if(nextyhigh >= po->getMinY(mypos)) this->nextyhigh = po->getMinY(mypos);
                    collided = 4;
                }
                
            }
        }
    }
    return collided;
}




/* Game Interface */
int Player::getDevice(){return device;}
void Player::setDevice(int device){this->device = device;}
int Player::getViewportX(){return viewportX;}
int Player::getViewportY(){return viewportY;}
void Player::setViewportX(int viewportX){this->viewportX = viewportX;}
void Player::setViewportY(int viewportY){this->viewportY = viewportY;}

float Player::getYHigh(){return yhigh;}
float Player::getYLow(){return ylow;}
void Player::setYHigh(float yhigh){this->yhigh = yhigh;}
void Player::setYLow(float ylow){this->ylow = ylow;}

void Player::enableGravity(){genabled = 1;lasttime = global_time;yspeed = 0;}
void Player::disableGravity(){genabled = 0;lasttime = global_time; yspeed = 0;}

void Player::gravity()
{
    nextY-= yspeed * 9 * (global_time - lasttime);
    yspeed+=0.01;
    if(nextY <= ylow+1){
        nextY = ylow+1;
        yspeed = 1;
    }else if(nextY >= yhigh-1){
        nextY = yhigh-1;
    }
    lasttime = global_time;
}
void Player::jump(int state){
    if(state){
        jumpbegin = global_time;
        yspeed = -0.5;
    }
}



