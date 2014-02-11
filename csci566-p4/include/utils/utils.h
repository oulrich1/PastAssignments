
/* This is the utility header:

    THis file includes all of 
    the useful code libraries
    that the rest of the program uses:

    including Angel.h, c std libs, c++ libs */
    
// #include <SOIL.h> // simple opengl image library

#include "Angel.h"
   


#include <sstream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <cmath>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// this might not need to be incldued
#include <cstdlib>
#include <GL/glut.h>

// there is an issue with Magick on my system 
 // #include <Magick++.h> 


#ifndef UTILS_H
#define UTILS_H

#define PTS_N_CUBE      8

#define SHADER_PATH(shader_name) ((string("shaders/") + shader_name).c_str())

typedef std::vector<float>                  VF; 
typedef std::vector<std::vector<float> >    VVF; 


using namespace std;

#define rand_f() ((float) rand() / (RAND_MAX))


struct pointpair {
    vec4 p1;
    vec4 p2;
};

static string toString(float f){
	stringstream sss;
	sss << f;
	return sss.str();
}

#endif