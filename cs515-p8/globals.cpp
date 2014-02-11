// globals.cpp

// CONTAINS DEFINITIONS OF THE DECLARATIONS IN GLOBALS.H

//  does not depend on ANY OTHER CODE TO FUNCTION PROPERly

#include "globals.h"


string toString(int x){
  stringstream ss;
  ss << x;
  return ss.str();
}
string toString(string s){
  return s;
}

double toDegrees(double rad){
    return (rad * 180)/ M_PI; // == degrees
}
double toRadians(double deg){
    return (deg * M_PI)/ 180; // == radians
}




//-------------------------------------------------//
/*                                                 */
/* Non-class functions                             */
/*                                                 */
//-------------------------------------------------//

// *********
//  ITOA
// *********

char* _itoa(int num){
  /*
  char* str = (char*)malloc(1);
  sprintf(str, "%d" , num);
  return str;
  */
  stringstream ss;
  ss << num;

  int strlength = strlen((ss.str()).c_str());

  char* str = (char*)malloc(strlength+1);
  memcpy(str, (ss.str()).c_str(), strlength+1);

  return str;
}

//******
// DTOA
char* _dtoa(double num){
  stringstream ss;
  ss << num;

  int strlength = strlen((ss.str()).c_str());

  char* str = (char*)malloc(strlength+1);
  memcpy(str, (ss.str()).c_str(), strlength+1);

  return str;
}

// NOT USED although i wanted to try it
// converts  "num_bytes"  bytes pointed to
//  by "x" 
//  into a string.. returns teh string
string        
toString(void* x, unsigned int bytes) {
  char* c = (char*)x;
  stringstream ss; 
  while(bytes--){ 
    ss << *((char*)c); 
    c++;
  } 
  return ss.str();
}


