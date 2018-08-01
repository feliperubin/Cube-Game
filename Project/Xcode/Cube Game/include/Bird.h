//
//  Bird.hpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 02/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Bird_h
#define Bird_h

#include "globals.h"
#include "PhysicalObject.h"
#include "../Models/BirdModel.h"
#include "../T1Files/video.h"
class Bird: public PhysicalObject{
public:
    Bird(void);
    ~Bird(void);
    void nextStage(void);
    void draw(void);
    void setTimeSeries(VideoInfo *vi, int birdId);
//    float getMinX(glm::vec3 pos);
//    float getMaxX(glm::vec3 pos);
//    float getMinY(glm::vec3 pos);
//    float getMaxY(glm::vec3 pos);
//    float getMinZ(glm::vec3 pos);
//    float getMaxZ(glm::vec3 pos);

private:
    int angle = 0;
    int up = 0;
    //T1 Related
    VideoInfo *vi;
    int birdId;
    int currentFrame;
    Point *prevPos;
};


#endif /* Bird_h */
