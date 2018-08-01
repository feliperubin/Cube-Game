//
//  Square.h
//  GLFWCameraView
//
//  Created by Felipe Rubin on 27/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Square_h
#define Square_h

#include "globals.h"
#include "PhysicalObject.h"
class Square: public PhysicalObject{
public:
    Square(void);
    ~Square(void);
    void nextStage(void);
    void draw(void);
    void setS(GLfloat s0,GLfloat s1,GLfloat s2,GLfloat s3);
    void setT(GLfloat t0,GLfloat t1,GLfloat t2,GLfloat t3);
    float getWidth(void);
    float getHeight(void);
    float getDepth(void);
    
    float getMinX(glm::vec3 pos);
    float getMaxX(glm::vec3 pos);
    float getMinY(glm::vec3 pos);
    float getMaxY(glm::vec3 pos);
    float getMinZ(glm::vec3 pos);
    float getMaxZ(glm::vec3 pos);
    
    
private:
    GLfloat s0 = 0,s1 = 0,s2 = 1,s3 = 1;
    GLfloat t0 = 0,t1 = 1 ,t2 = 1,t3 = 0;    
};
#endif /* Square_h */
