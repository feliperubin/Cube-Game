//
//  Gun.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 05/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "../include/Gun.h"
Gun::Gun()
{
    this->creationTime = global_time;
}
Gun::~Gun(){}
void Gun::nextStage(void){}
void Gun::setBulletTexture(GLuint *bulletTexture){this->bulletTexture = bulletTexture;}
void Gun::draw(void)
{


    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos, yPos, zPos); //O cano em q a bala fica quando a arma ta carregada
    glScalef(size,size,size);
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
    glTranslatef(xPos, yPos, zPos); //uma parte q n sei qq faz
    glScalef(size,size,size);
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
    glTranslatef(xPos, yPos, zPos); //negocio q tu puxa p/ carregar
    glScalef(size,size,size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
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

    
    static float release = 0;
    static int up = 1;
    if(release > 0.25) up = 0;
    if(release <= 0) up = 1;
    
    if(up){
        release+=0.05;
    }else{
        release-=0.05;
    }
    static float bulletRot = 0;

    if(up){
        bulletRot+=10;
    }else{
        bulletRot = 0;
    }
    glPushMatrix();
    glColor3f(1,1, 1);
    glTranslatef(xPos, yPos, zPos); //bala
    glRotatef(bulletRot, 0, 1, 0);
    glRotatef(bulletRot, 1, 0, 0);
    glScalef(size,size,size);
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
    glTranslatef(xPos, yPos, zPos); //corpo
    glScalef(size,size,size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
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
    glTranslatef(xPos, yPos, zPos+release);
//    glTranslatef(xPos,yPos,zPos); //negocio q vai pra tras e pra frente
    glScalef(size,size,size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture);
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
    glTranslatef(xPos, yPos, zPos); //Cartucho
    glScalef(size,size,size);
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







