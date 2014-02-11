
#ifndef CVTEST_CPP_INCLUDED
#define CVTEST_CPP_INCLUDED




#include <map>
#include <vector>
#include <windows.h>
#include <sstream>
#include <stdio.h>
#include <iostream> 


using namespace std;

#include "decide.h"
#include "stereo.h"
#include "Galil_IGV.h"

#include "globals.h"
/* ********************************** */
/* Begin Global Variable Declarations */
/* ********************************** */
char mode;

float MaxDens = .5;
float MaxWhiteDensity = 15;//15;

/* ******************************************************** */
/* Critical Section, Semaphore and Generic IPC Declarations */
/* ******************************************************** */

CRITICAL_SECTION RawDisparityMap;       //used between stereo --> line processes, temp1(RGB/XYZ)image -> (RGB/XYZ)image -> temp2(RGB/XYZ)image
//CRITICAL_SECTION GrabSemaMap;
CRITICAL_SECTION SetCommData;
CRITICAL_SECTION PostDecisionMap;       //used between line --> decision processes, FromVisionCircle -> GlobalCircle -> ToDecisionCircle
CRITICAL_SECTION GetDecisionMap;         //used between line --> decision processes, second half

/* ******************************************* */
/* Necessary Windows Multithreading Structures */
/* ******************************************* */
HANDLE NewImage, NewMap, NewCommData, EthernetUp;

DWORD tidVision, tidStereo, tidDecide;
// hMotion is in globals.h (defined as extern variable)
HANDLE hVision = 0, hStereo = 0, hDecide = 0;
HANDLE hMotion;

DWORD tidMotion;

 /* Logic Control Variables */  // not extern //
bool LineEscape;// = 0;
bool stopmain;// = false;
bool escape;// = false;


//////////////////
// Events
//////////////////

//An event to flag when new commands should be sent via Ethernet
//if hNewMotion is set and TermString is not empty, then the contents of TermString are sent
//else, the vector (long int speed, long int dir) is sent
HANDLE hNewMotion;

//An event to flag when the current command has been sent via Ethernet
HANDLE hMotionDone;

//An event to flag when the vehicle has been commanded to stop
//This is primarily used to ensure the vehicle is stopping before exiting the program
HANDLE hStopped;

//An event to flag when data has been received via Ethernet
HANDLE hNewRecv;

//////////////////
// Semaphores
//////////////////

//A mutex to protect char TermString[64];
//if hNewMotion is set and TermString is not empty, then the contents of TermString are sent
//else, the vector (long int speed, long int dir) is sent
HANDLE mTermString;
char TermString[64];

//A mutex to protect long int speed and long int dir
//if hNewMotion is set and TermString is not empty, then the contents of TermString are sent
//else, the vector (long int speed, long int dir) are sent
HANDLE mVector;
long int speed;
long int dir;

//A mutex to protect char* RecvPtr;
HANDLE mRecvPtr;
char* RecvPtr;

/* ******************** */
/* End Global Variables */
/* ******************** */


DWORD WINAPI MakeDecision(LPVOID param)
{
     //call function or include here
    while (!escape)
    {
        makeDecisions();
        //printf("starting doGo again.\n");
    }
    return 0;
}

DWORD WINAPI StereoProcessing(LPVOID param)
{
     //call function or include here
    RunStereo();
    return 0;
}

// Calls the MotionLoopGalil() from Galil_IGV.h; Which does motion stuff;
DWORD WINAPI MotionLoop(LPVOID param)
{
   //MotionLoopGalil(); // from GALIL_IGV.H
   return 0;
}

void StartThreads(int RunThreads)
{
	//printf("%d\n", RunThreads);
	InitializeCriticalSection(&RawDisparityMap);
	//InitializeCriticalSection(&GrabSemaMap);
	InitializeCriticalSection(&SetCommData);
	InitializeCriticalSection(&PostDecisionMap);
	InitializeCriticalSection(&GetDecisionMap);
	NewImage = CreateEvent(NULL, FALSE, FALSE, NULL);
	NewMap = CreateEvent(NULL, FALSE, FALSE, NULL);
	NewCommData = CreateEvent(NULL, FALSE, FALSE, NULL);
	hNewMotion = CreateEvent(NULL, FALSE, FALSE, NULL);
	hMotionDone = CreateEvent(NULL, FALSE, FALSE, NULL);
	hStopped = CreateEvent(NULL, FALSE, FALSE, NULL);
	EthernetUp = CreateEvent(NULL, TRUE, FALSE, NULL);      //must be manually reset; currently not used
	mTermString = CreateMutex(NULL, FALSE, NULL);               //TermString is used to send terminal strings to motion (afsocket) *
	mRecvPtr = CreateMutex(NULL, FALSE, NULL);                  //RecvPtr is used to send terminal strings to motion (afsocket) *
	mVector = CreateMutex(NULL, FALSE, NULL);                   //vector (and mVector) is used to communicate btwn. decide and motion (afsocket)

  
    if ((RunThreads & STEREOID) && (hStereo == 0))
    {
		//printf("%d\n", RunThreads);
		printf("Starting hStereo.\n");
        hStereo = (HANDLE) CreateThread(NULL, 0, StereoProcessing, 0, CREATE_SUSPENDED, &tidStereo);
        SetThreadPriority(hStereo, THREAD_PRIORITY_NORMAL);
		/* Add Processor Affinities Here? */
		ResumeThread(hStereo);
	}

	if ((RunThreads & DECIDEID) && (hDecide == 0))
	{
		//printf("%d\n", RunThreads);
		printf("Starting hDecide.\n");
		hDecide = (HANDLE) CreateThread(NULL, 0, MakeDecision, 0, CREATE_SUSPENDED, &tidDecide);
		SetThreadPriority(hDecide, THREAD_PRIORITY_NORMAL);
		/* Add Processor Affinities Here? */
		ResumeThread(hDecide);
  } 

  if ((RunThreads & MOTIONID) && (hMotion == 0))
	{
	    printf("Starting hMotion.\n");
	    hMotion = (HANDLE) CreateThread(NULL, 0, MotionLoop, 0, CREATE_SUSPENDED, &tidMotion);
	    SetThreadPriority(hMotion, THREAD_PRIORITY_NORMAL);
	    /* Add Processor Affinities Here? */
	    ResumeThread(hMotion);
	}
}

void StopThreads()
{
	if (hStereo)
		CloseHandle(hStereo);
	if (hVision)
		CloseHandle(hVision);
	if (hDecide)
		CloseHandle(hDecide);
  if (hMotion)
    CloseHandle(hMotion);
	DeleteCriticalSection(&RawDisparityMap);
	DeleteCriticalSection(&SetCommData);
	DeleteCriticalSection(&PostDecisionMap);
	DeleteCriticalSection(&GetDecisionMap);
}

int main()
{
	//StartThreads(STEREOID | VISIONID | DECIDEID | MOTIONID);
  StartThreads(STEREOID | DECIDEID | MOTIONID);
	char defmode = mode = AUTOMODE;
	long int prevspeed = 0, prevdir = 0, locspeed = 0, locdir = 0;
	while(!GetAsyncKeyState(VK_ESCAPE) && !stopmain)
	{
	    if (GetAsyncKeyState(VK_SHIFT))//(GetKeyState(VK_CAPITAL) & 0x01)
	    {
	        //CAPS LOCK is on
	        //run manual
            
	          if (mode != MANUALMODE)
	          {
	              //Tell it to stop
                  mode = MANUALMODE;
                  WaitForSingleObject(mVector, INFINITE);
                  speed = 0;
                  dir = 0;
                  ReleaseMutex(mVector);
                  SetEvent(hNewMotion);
	          }
            printf("ManualMode");
            do
            {
                if (GetAsyncKeyState('W') && !GetAsyncKeyState('S'))
                {
                    locspeed = 10;
                }
                else if (GetAsyncKeyState('S') && !GetAsyncKeyState('W'))
                {
                    locspeed = -4;
                }
                else
                {
                    locspeed = 0;
                }
                if (GetAsyncKeyState('A') && !GetAsyncKeyState('D'))
                {
                    locdir = -15;
                }
                else if (GetAsyncKeyState('D') && !GetAsyncKeyState('A'))
                {
                    locdir = 15;
                }
                else
                {
                    locdir = 0;
                }
                if (GetAsyncKeyState(VK_CONTROL))
                {
                    printf("Telling GPS thread to store cur GPS...\n");
                    while(GetAsyncKeyState(VK_CONTROL)){};
                }
                //printf("speed: %f\ndir: %ld\n", speed, dir);
            } while (locspeed == prevspeed && locdir == prevdir && !GetAsyncKeyState(VK_ESCAPE) && GetAsyncKeyState(VK_SHIFT));
            prevspeed = locspeed;
            prevdir = locdir;
            WaitForSingleObject(mVector, INFINITE);
            speed = locspeed;
            dir = locdir;
            //printf("dir: %f\n", dir);
            ReleaseMutex(mVector);
            SetEvent(hNewMotion);
	    }
	    else 
	    {
	        //printf("Auto Mode\n");
            //CAPS LOCK is off
	        //reset to whatever the original mode was
	        if (mode != defmode)
	        {
	            //printf("Auto mode\n");
	            mode = defmode;
	        }
	    }
    } // end while

	printf("Stopping...\n");
    WaitForSingleObject(mVector, INFINITE);
    speed = 0;
    dir = 0;
    //printf("dir: %f\n", dir);
    ReleaseMutex(mVector);
    SetEvent(hNewMotion);
    WaitForSingleObject(hStopped, INFINITE);
	escape = true;
	if (!stopmain)
	{
        while(GetAsyncKeyState(VK_ESCAPE));
	}
	StopThreads();
	return 0;
}

#endif
