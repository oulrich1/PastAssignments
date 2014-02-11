#pragma once
#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

///This file (globals.h) includes actual global variable instantiation, and therefore must only be included once.
///Global variables, if used by a file other than that which directly includes, must be defined as extern.

#include <windows.h>
#include <time.h>
#include <math.h>


///     Notes:
/// (1) CRITICAL_SECTIONs and mutexes are used for thread synchronization and IPC.  CRITICAL_SECTIONs were generally preferred
///     because they operate faster (approx. 10-30+ times faster than a mutex).  Within the CRITICAL_SECTION, the local* variable
///     from the first thread copied to a global variable, which then using another CRITICAL_SECTION can be copied to a local*
///     variable within the receiving thread.
///         * Local variables are not used for large sections of memory, we suspect due to the nature of the program being
///           multithreaded as opposed to multiprocessed (better).  Multiprocessing might provide more resources to each task than
///           is afforded by multithreading.
///
///     The generic method for using a CRITICAL_SECTION as a semaphore is:
///         //Initialization (Thread 0)
///         CRITICAL_SECTION cs_source, cs_dest;
///         InitializeCriticalSection(&cs_source);
///         InitializeCriticalSection(&cs_dest);
///         ...
///         //Posting the semaphore (Thread 1)
///         EnterCriticalSection(&cs_source);
///         memcpy(dest_global, source_local, sizeof(dest_global));
///         LeaveCriticalSection(&cs_source);
///         memset(source_local, 0, sizeof(source_local));
///         ...
///         //Grabbing the semaphore (Thread 2)
///         memset(dest_local, 0, sizeof(dest_local));
///         EnterCriticalSection(&cs_dest);
///         memcpy(dest_local, dest_global, sizeof(dest_local));
///         LeaveCriticalSection(&cs_dest);
///         ...
///         //Deletion (Thread 0)
///         DeleteCriticalSection(&cs_source);
///         DeleteCriticalSection(&cs_dest);
///     Note: Threads 1 and 2 should be suspended or stopped before the CRITICAL_SECTIONs are deleted.
///
/// (2) Mutexes are occasionally used, as follows:
///         //Initialization (Thread 0)
///         HANDLE m1;
///         mdata1 = CreateMutex(NULL, FALSE, NULL);
///         <type> data1;
///         ...
///         //Posting or Grabbing the semaphore (Thread 1 or 2, etc.)
///         WaitForSingleObject(mdata1, INFINITE);
///         //modify data1 here
///         ReleaseMutex(mdata1);
///         ...
///         //Deletion
///         //None (?)
///     Note: Threads accessing the mutex should always release the mutex before being stopped or suspended

#define PI 3.14159265359
#define TODEG 180/PI
#define TORAD PI/180

#define MTOIN 39.3700787        //meters to inches conversion factor

#define STEREOID 00000001
#define VISIONID 00000010
#define GPSID 00000100
#define COMPASSID 00001000
#define DECIDEID 00010000
#define MOTIONID 00100000

#define MANUALMODE 00000000
#define AUTOMODE 00000001
#define GPSMODE 00000010
extern char mode;// = MANUALMODE;

//#include "gps.h"
//#include "compass.h"

//#include "calfile.h"

#define CAMANG -15//-17		//angle at which camera is mounted (in degrees)
#define CAMANGTOL 1         //tolerance for the angle (in degrees)
#define CAMH .47625//.38		//height at which the camera is mounted (in meters)
#define CAMHTOL 0.1         //tolerance for the height (in meters)
#define CAMHTOLDOWN 0.1     //additional tolerance down (for descending ramps)
#define MAXGRAD .15         //maximum climbable gradient of the vehicle

#define BOTWIDTH 0.9	    //width of bot in meters

/* Keyboard constants. Used in: Galil_IGV */
#define w_key 0x57 
#define a_key 0x41 
#define s_key 0x53 
#define d_key 0x44 

#define W_key 0x57 
#define A_key 0x41 
#define S_key 0x53 
#define D_key 0x44 


extern float MaxDens;// = .5;
extern float MaxWhiteDensity;// = 15;//15;

/* ********************************** */
/* Begin Global Function Declarations */
/* ********************************** */

void delay(int dseconds);

void mdelay(unsigned int mseconds);

float sqr(float x);

/* ******************************** */
/* End Global Function Declarations */
/* ******************************** */

/* ********************************** */
/* Begin Global Structure Definitions */
/* ********************************** */


/* Begin Global Structures */
struct rgb
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct xyz
{
	float x;
	float y;
	float z;
	float xz;
};

struct slope
{
	float x;
	float z;
	float m;
	bool valid;
	float variance;
};

struct col
{
	float z;
	int cnt;
};
/* End Global Structures */

/* ********************************** */
/* Begin Global Variable Declarations */
/* ********************************** */

/* ******************************************************** */
/* Critical Section, Semaphore and Generic IPC Declarations */
/* ******************************************************** */

extern CRITICAL_SECTION RawDisparityMap;       //used between stereo --> line processes, temp1(RGB/XYZ)image -> (RGB/XYZ)image -> temp2(RGB/XYZ)image
//CRITICAL_SECTION GrabSemaMap;
extern CRITICAL_SECTION SetCommData;
extern CRITICAL_SECTION PostDecisionMap;       //used between line --> decision processes, FromVisionCircle -> GlobalCircle -> ToDecisionCircle
extern CRITICAL_SECTION GetDecisionMap;         //used between line --> decision processes, second half

/* ******************************************* */
/* Necessary Windows Multithreading Structures */
/* ******************************************* */
extern HANDLE NewImage, NewMap, NewCommData, EthernetUp;

extern DWORD tidVision, tidStereo, tidDecide;
extern HANDLE hVision, hStereo, hDecide;

/* Logic EXTERNAL Control Variables */

extern bool LineEscape;// = 0;
extern bool stopmain;// = false;
extern bool escape;// = false;

//const int mapwidth[16] = {7, 9, 9, 11, 13, 13, 15, 15, 17, 19, 19, 21, 23, 23, 25, 27};



/* *********************************** */
/* Begin afsocket.h Global Definitions */
/* *********************************** */

extern HANDLE hMotion;

extern DWORD tidMotion;

extern bool CONNECT_TO_GALIL;

extern bool STOP_MOTION;

//motion variables: formally declared in Galil_IGV.. modified by decision code
extern float gDX;
extern float gDY;

//////////////////
// Events
//////////////////

//An event to flag when new commands should be sent via Ethernet
//if hNewMotion is set and TermString is not empty, then the contents of TermString are sent
//else, the vector (long int speed, long int dir) is sent
extern HANDLE hNewMotion;

//An event to flag when the current command has been sent via Ethernet
extern HANDLE hMotionDone;

//An event to flag when the vehicle has been commanded to stop
//This is primarily used to ensure the vehicle is stopping before exiting the program
extern HANDLE hStopped;

//An event to flag when data has been received via Ethernet
extern HANDLE hNewRecv;

//////////////////
// Semaphores
//////////////////

//A mutex to protect char TermString[64];
//if hNewMotion is set and TermString is not empty, then the contents of TermString are sent
//else, the vector (long int speed, long int dir) is sent
extern HANDLE mTermString;
extern char TermString[64];

//A mutex to protect long int speed and long int dir
//if hNewMotion is set and TermString is not empty, then the contents of TermString are sent
//else, the vector (long int speed, long int dir) are sent
extern HANDLE mVector;
extern long int speed;
extern long int dir;

//A mutex to protect char* RecvPtr;
extern HANDLE mRecvPtr;
extern char* RecvPtr;

/* End Global Variables */

#endif // GLOBALS_H_INCLUDED
