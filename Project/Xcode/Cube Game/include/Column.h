//
//  Column.hpp
//  GLFWCameraView
//
//  Created by Felipe Rubin on 02/06/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef Column_h
#define Column_h
#include "globals.h"
#include "PhysicalObject.h"
#include "../Models/ColumnModel.h"
class Column: public PhysicalObject{
public:
    Column(void);
    ~Column(void);
    void nextStage(void);
    void draw(void);
    float getMinX(glm::vec3 pos);
    float getMaxX(glm::vec3 pos);
    float getMinY(glm::vec3 pos);
    float getMaxY(glm::vec3 pos);
    float getMinZ(glm::vec3 pos);
    float getMaxZ(glm::vec3 pos);

};

#endif /* Column_h */
