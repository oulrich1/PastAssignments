/*  GALIL_IGV.H
    Provides communication to Galil
    Used to provide the Galil with commands to move the wheels
    */

#include <map>
#include <vector>
#include <windows.h>
#include <sstream>
#include <iostream> //cout

#include "globals.h"

#include "include/XInput.h"
#include "include/Galil.h" //include Galil header file

#include <iomanip> //needed to format the DR output


#ifndef GALIL_IGV_H
#define GALIL_IGV_H

using namespace std;

/*******************************/
/**    FIELDS    **/
/*******************************/  
static bool STOP_MOTION;

static float gDX; // magnitude is somewhere in the thousands to tens of thousands.
static float gDY;

/*******************************/
/**    FUNCTION PROTOTYPES    **/
/*******************************/   

// First Function Called:::
//This is the main MotionLoop that connects to the galil and executes motion. 
//(this function is called by MotionLoop() in IGV_main.cpp. MotionLoop() is a threaded function.
void MotionLoopGalil();



bool initXBOX360Controller(int controller_number, XINPUT_STATE &CONTROLLER);
DWORD initGalil(Galil* &g);



// simple test (turns motor on until a key is pressed)
DWORD getGalilAddresses(vector<string> &addresses); // LINE # 176
void printLibraryVersion();                         // LINE # 191


// depends on global variables from GLOBALS_H (returns error code)
DWORD commandIGV(Galil* &g);

// depends on XBOX360 controller being connected
void control_IGV(Galil &g, XINPUT_STATE &prev_state);


/**     Begin Control of IGV with KEYBOARD    **/
void control_IGV_with_KEYBOARD(Galil* &g);


// stops all motion
bool stopMotion();
/**********************************/
/**    END FUNCTION PROTOTYPE    **/
/**********************************/

// Helpers::
string toString(float num);
string toString(int num);


#endif 