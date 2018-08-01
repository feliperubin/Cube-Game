//
//  BirdModel.h
//  GLFWCameraView
//
//  Created by Felipe Rubin on 03/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef BIRDMODEL_H
#define BIRDMODEL_H
#include "globals.h"
extern const int tLeftWingSize;
extern const int vLeftWingSize;
extern const int tRightWingSize;
extern const int vRightWingSize;
extern const int tBodySize;
extern const int vBodySize;
extern const int tTailSize;
extern const int vTailSize;
extern const int tBeakSize;
extern const int vBeakSize;
extern float bminX,bminY,bminZ,bmaxX,bmaxY,bmaxZ;

extern GLfloat vLeftWing[];
extern GLfloat vRightWing[];
extern GLfloat vBody[];
extern GLfloat vTail[];
extern GLfloat vBeak[];


extern GLfloat tLeftWing[];
extern GLfloat tRightWing[];
extern GLfloat tBody[];
extern GLfloat tTail[];
extern GLfloat tBeak[];

#endif /* BIRDMODEL_H */
