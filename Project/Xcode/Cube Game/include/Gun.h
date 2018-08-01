//
//  Gun.hpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 05/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Gun_h
#define Gun_h
#include "globals.h"
#include "PhysicalObject.h"
//#include "../Models/CartoonBoyModel.h"
#include "../Models/GunModel.h"
class Gun: public PhysicalObject{
public:
    Gun(void);
    ~Gun(void);
    void nextStage(void);
    void draw(void);
    void setBulletTexture(GLuint *bulletTexture);
private:
    GLuint *bulletTexture;
    std::vector<glm::vec3> vecindices;
    std::vector<glm::vec2> vectexture;
    std::vector<glm::vec3> vecnormals;
    
    std::vector<std::vector<glm::vec3>> verts;
    std::vector<std::vector<glm::vec3>> norms;
    std::vector<std::vector<glm::vec2>> textrs;


};

#endif /* Gun_h */
