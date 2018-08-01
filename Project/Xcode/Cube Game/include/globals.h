//
//  globals.h
//  GLFWCameraView
//
//  Created by Felipe Rubin on 29/05/18.
//  Copyright © 2018 Felipe Rubin. All rights reserved.
//

#ifndef globals_h
#define globals_h
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
#include <OpenGL/gl.h>

//General C/C++ Libs
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <limits.h>
#include <iostream>
//#include <algorithm>
//#include <fstream>

//Matrix Mathematics
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>


//Reads Files
#include "SOIL2.h"
#include <fstream>


//Audio Lib
//#include <irrKlang.h>





extern double global_time; //App time since started

#endif /* globals_h */
