// globals.h
// CONTAINS GLOBAL FUNCTIONS TO BE USED ANYWHERE
//  
// CONTEXT  SPECIFIC  INCLUDES
//  (GPL SPECIFIC)

#include "gpl_type.h"
#include "gpl_assert.h"
#include "error.h"

#include "game_object.h"
#include "triangle.h"
#include "pixmap.h"
#include "circle.h"
#include "rectangle.h"
#include "textbox.h"   

#include "animation_block.h"


//  does not depend on ANY OTHER CODE TO FUNCTION PROPERly
#ifndef GLOBALS_H
#define GLOBALS_H


#include <sstream>

#include <string>
#include <map>
#include <ostream>
#include <iostream>

#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <time.h>

using namespace std;

typedef unsigned int u_int;
#ifndef M_PI
#define M_PI 3.1415926535897932
#endif


string              toString(int x);
string              toString(string s);

double              toDegrees(double rad);
double              toRadians(double deg);

///  TO STRING  ///


char*               _itoa(int    num);                           
char*               _dtoa(double num);



string              toString(void* x, u_int bytes);


#endif