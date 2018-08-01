//
//  cgutils.cpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 31/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#include "cgutils.h"
#include "SOIL2.h"

void loadTexture(GLuint *tx,char* imgpath,GLint param0,GLint param1, GLint param2, GLint param3)
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, tx);
    glBindTexture(GL_TEXTURE_2D, *tx);
    int imgw,imgh;
    unsigned char *tximg = SOIL_load_image(imgpath, &imgw, &imgh, 0, SOIL_LOAD_RGBA);
    glTexImage2D( *tx, 0, GL_RGBA, imgw, imgh, 0, GL_RGBA, GL_UNSIGNED_BYTE, tximg );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param3);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,imgw,imgh,GL_RGBA, GL_UNSIGNED_BYTE,tximg);
    SOIL_free_image_data( tximg );
    glBindTexture(GL_TEXTURE_2D,0);
    glDisable(GL_TEXTURE_2D);
}


void loadTexture3D(GLuint *tx,char* imgpath)
{
    glEnable(GL_TEXTURE_3D);
    glGenTextures(1, tx);
    glBindTexture(GL_TEXTURE_3D, *tx);

    int imgw,imgh,imgd;
    unsigned char *tximg = SOIL_load_image(imgpath, &imgw, &imgh, &imgd, SOIL_LOAD_RGBA);
    glTexImage3D( *tx, 0, GL_RGBA, imgw, imgh,100, 1, GL_RGBA, GL_UNSIGNED_BYTE,tximg );
    gluBuild3DMipmaps(GL_TEXTURE_3D, GL_RGBA, imgw, imgh, 1, GL_RGBA, GL_UNSIGNED_BYTE, tximg);
    SOIL_free_image_data(tximg);
    glBindTexture(GL_TEXTURE_3D,0);
    glDisable(GL_TEXTURE_3D);
}








