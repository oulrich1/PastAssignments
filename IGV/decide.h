///// HEADER FILE
/// DECIDE.H

#include "globals.h"
#include <iostream>
using namespace std;

#ifndef DECIDE_H
#define DECIDE_H
/// FILE IN WHICH DECISIONS ARE DELEGATED

// Function that makes decisions on where/how to move the IGV (communicates to galil)
// decisions are based on the data set in globals.h/globals by
// ( saved_data/data from StereoCamera, GPS, Compass, Galil, network?, ...?)
void makeDecisions(); 


#endif