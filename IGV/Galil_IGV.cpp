/**
STL LIBRARY EXAMPLE
Library: Galil2.dll 2.0.2.471
Last Updated: 11.09.12
Author: RP

COMPILE:
Microsoft Visual C++ Release
cl filename.cpp Galil2.lib Xinput.lib -EHsc -MD
(must be compiled with and run with the binaries from the release directory)

Microsoft Visual C++ Debug
cl filename.cpp Galil2.lib Xinput.lib -EHsc -MDd
(must be compiled with and run with the binaries from the debug directory)

RUN:
filename.exe
**/


#include "Galil_IGV.h"



#define LEFT_THUMB_DEADZONE  7849
#define RIGHT_THUMB_DEADZONE 8689
#define TRIGGER_THRESHOLD    30

#define THUMB_MAX 32767
#define LY_MAX (THUMB_MAX - LEFT_THUMB_DEADZONE)
#define LX_MAX LY_MAX

/*                                             */
//*          FUNCTION IMPLEMENTATIONS         *//
/*                                             */

// TO STRING FUNCTIONS
string toString(float num){
    stringstream ss;
    ss << num;
    return ss.str();
}
string toString(int num){
    stringstream ss;
    ss << num;
    return ss.str();
}


// stop motion
bool stopMotion(){
    STOP_MOTION = true;
}

/********************************                       **/
/**    BEGIN MAIN MOTIONLOOPGALIL  (IGV's main motion loop)  **/
/********************************                       **/
void MotionLoopGalil(){
    try{
        Galil *g; // if passing this to other functions does not work when passed as a pointer.. then i need to pass it by value (*g)
        bool WAS_CONNECTED = false;
        bool CONNECT_TO_GALIL = true;

        DWORD dwresult = 0;

        while(!escape){ // BEGIN MAIN GALIL MOTION LOOP
            if(CONNECT_TO_GALIL && !WAS_CONNECTED){             // IF IT NEEDS TO CONNECT AND IT WAS NOT CONNECTED
                dwresult = initGalil(g);                        // connect g to a GAlIL (returns with error (0 if no error))           
                if(dwresult == 0){
                    WAS_CONNECTED = true;
                } else {
                    cerr << "Couldnt Connect to Galil, Unknown Error" << endl;
                }
            }
            
            if(CONNECT_TO_GALIL && WAS_CONNECTED){               // then connect
                
                //commandIGV(g);                                  /// EXECUTE THE IGV COMMAND ROUTINE
                control_IGV_with_KEYBOARD(g);
            }
            WAS_CONNECTED = false;                               // AT THIS POINT l.. if commandIGV isnt doing stuff then it isnt connected.. therefore false
        }               


    }catch(string e){ //catch any errors
        cout << "Caught Exception: " << e;
        if(string::npos != e.find("COMMAND ERROR"))
            cout << "  " << "Command error!" << endl;  //process command errors
    }
}
/**********************************/
/**      END MOTIONLOOPGALIL     **/
/**********************************/

//**********************************
//** INIT GALIL (excepts a pointer to a GALIL passed by reference)   
//**  output --> g points to a GALIL and GALIL can be sent commands
DWORD initGalil(Galil* &g){
    /// CONNECTION INITIALIZATING WITH/TO GALIL :::
    // most of the time this has been the IP address of the galil
    /// default address and COM1 port:
    string GALIL_IP_ADDRESS      = "169.254.159.73";
    string GALIL_COM_PORT        = "COM1 19200";
    string GALIL_CONNECTION_INFO = GALIL_IP_ADDRESS;

    ///   some connection logic, controls => [ETHERNET or SERIAL, and then DEFAULT?]
    bool USE_ETHERNET = true;
    bool USE_SERIAL = !USE_ETHERNET;
    bool USE_DEFAULT_COM_IPADDRESS = true; /// set to true if i want to use the default values i have specified

    bool USE_DEFAULT_IPADDRESS = USE_ETHERNET && USE_DEFAULT_COM_IPADDRESS; /// IS TRUE then try and force an IP ADDRESS
    bool USE_DEFAULT_COMPORT = USE_SERIAL && USE_DEFAULT_COM_IPADDRESS;

    if(USE_DEFAULT_COMPORT){
        GALIL_CONNECTION_INFO = GALIL_COM_PORT;
    }

    vector<string> addresses; //all controllers vector

    DWORD validAddress = getGalilAddresses(addresses);  // FETCH GALIL ADDRESSES (set vector) (returns result code)
    //printLibraryVersion();

    // *** SET UP GALIL CONNECTION *** \\
    // set up a galil connection., (time for some business) (NOTE: must be in try catch blocks
    try{

        if(validAddress || USE_DEFAULT_IPADDRESS || USE_DEFAULT_COMPORT)
        { /// THEN: TRY TO CONNECT

            if(USE_DEFAULT_IPADDRESS || USE_DEFAULT_COMPORT){
                cout << "Connecting to " << GALIL_CONNECTION_INFO << endl;
                g = new Galil(GALIL_CONNECTION_INFO);
            } else {
                cout << "Connecting to " << addresses[0] << endl;
                g = new Galil(addresses[0]); // //Ethernet
            }
            g->timeout_ms = 5000;
            cout <<  "Connection Established!" << endl << endl;

            // DO SOMETHING WITH GALIL g
            //simpleMotorTest(g);         // *******************    
        } else {
            // g is empty;
            cout << "Failed To Connect, Didn't Find A Valid Address (press back)" << endl;
        }

    }catch(string e){ //catch any errors
        cout << "Caught Exception: " << e;
        if(string::npos != e.find("COMMAND ERROR"))
            cout << "  " << "Command error!" << endl;  //process command errors
        return 1;
    }
    return 0;
}



/**********************************/
/**   GET CONTROLLER INIT STATE  **/
/**********************************/
// ** Param1 === controller_number 
// ** Param2 === Controller State
// ** returns false on controller connection fail 
bool initXBOX360Controller(int controller_number, XINPUT_STATE &CONTROLLER){
    // **** XBOX 360 CONTROLLER INIT **** //
    // does not depend on how many controller are ACTUALLY CONENCTED
    // shoudl always be 1 anyways.. unless multiple controllers are needed to control
    //  other things? (if there is ever a need?)
    DWORD numberOfControllers = 1;
    DWORD dwresult;
    DWORD CONTROLLER_ID = controller_number;
    // CONTROLLER INTERFACE
    ZeroMemory( &CONTROLLER, sizeof(XINPUT_STATE));
    dwresult = XInputGetState(CONTROLLER_ID, &CONTROLLER);   // sets CONTROLLER1... (and returns a result)
    // now i have the state of the controller... check the result of calling the state.
    if(dwresult == ERROR_SUCCESS){
        // successful connection
        cout << "SUCCESS: Connected to XBOX controller: " << CONTROLLER_ID << endl;
        return true;
    } else{
        // not connected
        cerr << "ERROR: couldn't connect to XBOX controller: " << CONTROLLER_ID << endl;
        return false;
    }
    // NOW WE HAVE a STATE called CONTROLLER;
    // THIS HOLDS THE XINPUT_STATE of the controller we are concerned about.

    // *********end controller init*********
    return false;
}


// **  GET ADDRESSES THAT THE GALIL IS CONNECTED TO
//  (and prints onto the screen the list of addresses if any were found, including COM ports)
DWORD getGalilAddresses(vector<string> &addresses){
    DWORD RESULT;
    cout << endl << "Aquiring Galil IP addresses..." << endl;

    addresses = Galil::addresses(); //get all available controllers connections

    cout << "Listing addresses found: " << endl;
    if(addresses.size() == 0){
        cout << " - none - " << endl;
        RESULT = 0; // the addresses vector does not contain a valid address
    }
    else{
        for(int i = 0; i < (int)addresses.size(); i++){  // print out the addresses that i found
            cout << addresses[i] << endl;
        }
        RESULT = 1; // it contains at least 1 valid address..
    }
    return RESULT;
} // END GETADDRESSES



void printLibraryVersion(){
    cout << endl << "Listing library Version...";
    cout << endl << "  " << Galil::libraryVersion() << endl; //print lib version
    return;
}






/****************************                        ******/
/**    BEGIN CONTROL OF IGV USING SOME CONTROL MECHANISM:
    XBOX 360 CONTROLLER, some GLOBAL VARIABLE, and KeyBOARD **/
/****************************                        ******/
/* called in main. */
// ASSUMES 'g' IS VALID and points to Galil object
void control_IGV(Galil &g, XINPUT_STATE &prev_state){
    // LEFT_THUMB_DEADZONE; // experiemental value(anywhere from 0-65534)
    // GALIL SPECS:
    string RIGHT_MOTOR_JGPOWER_str = "";
    string LEFT_MOTOR_JGPOWER_str = "";

    int RIGHT_MOTOR_ACCELERATION  =   25000;
    int RIGHT_MOTOR_DECCELERATION =   45000;
    int RIGHT_MOTOR_JGPOWER_MAX   =   55000;  //definitely should not use that..

    int LEFT_MOTOR_ACCELERATION   =   RIGHT_MOTOR_ACCELERATION;
    int LEFT_MOTOR_DECCELERATION  =   RIGHT_MOTOR_DECCELERATION;
    int LEFT_MOTOR_JGPOWER_MAX    =   RIGHT_MOTOR_JGPOWER_MAX;

    g.commandValue("AC ," + toString(RIGHT_MOTOR_ACCELERATION) + "; "
        + "DC ," + toString(RIGHT_MOTOR_DECCELERATION) + "; "
        + "JG 0,0;");

    g.commandValue("BG;");   // BEGIN THE GALIL EXECUTION

    XINPUT_STATE state;
    ZeroMemory( &state, sizeof(XINPUT_STATE) );
    DWORD dwresult = XInputGetState(0, &state);

    float LX;
    float LY;
    float magnitude;
    float normalizedLX;
    float normalizedLY;
    float normalizedMagnitude;

    int cur_rightPower  = 0;
    int cur_leftPower   = 0;
    int prev_rightPower = 0;
    int prev_leftPower  = 0;

    while(state.Gamepad.wButtons != XINPUT_GAMEPAD_BACK){
        LX = state.Gamepad.sThumbLX;
        LY = state.Gamepad.sThumbLY;

        magnitude = sqrt(LX*LX + LY*LY);
        normalizedLX = LX/magnitude;
        normalizedLY = LY/magnitude;

        // tune X's and Y's for the Deadzones
        if(abs(LX) < LEFT_THUMB_DEADZONE){
            LX = 0;
        }
        else{
            LX -= LEFT_THUMB_DEADZONE;
        }
        if(abs(LY) < LEFT_THUMB_DEADZONE){
            LY = 0;
        }
        else{
            LY -= LEFT_THUMB_DEADZONE;
        }

        RIGHT_MOTOR_JGPOWER_str = toString(cur_rightPower = int((LY/LY_MAX) * (RIGHT_MOTOR_JGPOWER_MAX)  -  (LX/LX_MAX) * (LEFT_MOTOR_JGPOWER_MAX)));
        LEFT_MOTOR_JGPOWER_str  = toString(cur_leftPower = int((LY/LY_MAX) * (RIGHT_MOTOR_JGPOWER_MAX)  +  (LX/LX_MAX) * (LEFT_MOTOR_JGPOWER_MAX)));

        if(magnitude > LEFT_THUMB_DEADZONE){ // then we want to consider what it does
            if(magnitude > THUMB_MAX) // max thumbing
                magnitude = THUMB_MAX;

            // make sure the magnitude is the actual magnitude of that i need to consider
            magnitude -= LEFT_THUMB_DEADZONE;
            normalizedMagnitude = magnitude/(THUMB_MAX - LEFT_THUMB_DEADZONE);    // this is a percentage of the possible strength of the magnitude

            // RIGHT MOTOR TEST WITH MAGNITUDE OF THUMB STICK MOVEMENT (NOT NEEDED ANYMORE.. USING COMPONENTS LX and LY to DETERMINE MOVEMENT.
            //RIGHT_MOTOR_JGPOWER_str = toString(RIGHT_MOTOR_JGPOWER_MAX * normalizedMagnitude);
            //cout << RIGHT_MOTOR_JGPOWER_str << endl;
            //cout << g.commandValue("MG @ABS[-2.37]; MG " + RIGHT_MOTOR_JGPOWER_str + ";") << endl;
        }
        else{
            magnitude = 0;
            normalizedMagnitude = 0;
        }// end DEADZONE CHECK

        // now i can send the motor commands accordingly
        // if the power to left or right is different then send it to galil.. else dont send anything:
        if((cur_rightPower != prev_rightPower) || (cur_leftPower != cur_leftPower)){
            g.commandValue("JG " + LEFT_MOTOR_JGPOWER_str + "," + RIGHT_MOTOR_JGPOWER_str + ";");
            cout << "JG " + LEFT_MOTOR_JGPOWER_str + "," + RIGHT_MOTOR_JGPOWER_str + ";" << endl;
        }
        prev_leftPower = cur_leftPower;
        prev_rightPower = cur_rightPower;

        if(STOP_MOTION == true){
            break;
        }

        dwresult = XInputGetState(0, &state); // to get status and next state..
    }// end while

    g.commandValue("ST;");
    cout << "no longer controlling IGV with controller" << endl;
    return;
}
/****************************   ******/
/**    END control_IGV    **/
/****************************   ******/




/****************************                        ******/
/**    BEGIN COMMAND OF IGV USING GLOBAL VAIRALBES       **/
/****************************                        ******/
/* called in main. */
// ASSUMES 'g' IS VALID and points to Galil object (g is passed in as a pointer and not dereferenced)
DWORD commandIGV(Galil* &g){

    double dresult ;

    // LEFT_THUMB_DEADZONE; // experiemental value(anywhere from 0-65534)
    // GALIL SPECS:
    string RIGHT_MOTOR_JGPOWER_str = "";
    string LEFT_MOTOR_JGPOWER_str = "";

    int RIGHT_MOTOR_ACCELERATION  =   25000;
    int RIGHT_MOTOR_DECCELERATION =   45000;
    int RIGHT_MOTOR_JGPOWER_MAX   =   55000;  //definitely should not use that..

    int LEFT_MOTOR_ACCELERATION   =   RIGHT_MOTOR_ACCELERATION;
    int LEFT_MOTOR_DECCELERATION  =   RIGHT_MOTOR_DECCELERATION;
    int LEFT_MOTOR_JGPOWER_MAX    =   RIGHT_MOTOR_JGPOWER_MAX;

    g->commandValue("AC ," + toString(RIGHT_MOTOR_ACCELERATION) + "; "
        + "DC ," + toString(RIGHT_MOTOR_DECCELERATION) + "; "
        + "JG 0,0;");

    g->commandValue("BG;");   // BEGIN THE GALIL EXECUTION

    float LX;
    float LY;
    float magnitude;
    float normalizedLX;
    float normalizedLY;
    float normalizedMagnitude;

    int cur_rightPower  = 0;
    int cur_leftPower   = 0;
    int prev_rightPower = 0;
    int prev_leftPower  = 0;

    // while the galil is connected
    while(true){
        LX = gDX;   // THESE VALUES DETERMINE MOTION... SEE GLOBALS.H .. 
        LY = gDY;

        magnitude = sqrt(LX*LX + LY*LY);
        normalizedLX = LX/magnitude;
        normalizedLY = LY/magnitude;

        // tune X's and Y's for the Deadzones
        if(abs(LX) < LEFT_THUMB_DEADZONE){
            LX = 0;
        }
        else{
            LX -= LEFT_THUMB_DEADZONE;
        }
        if(abs(LY) < LEFT_THUMB_DEADZONE){
            LY = 0;
        }
        else{
            LY -= LEFT_THUMB_DEADZONE;
        }

        RIGHT_MOTOR_JGPOWER_str = toString  (cur_rightPower = int((LY/LY_MAX) * (RIGHT_MOTOR_JGPOWER_MAX)  -  (LX/LX_MAX) * (LEFT_MOTOR_JGPOWER_MAX)));
        LEFT_MOTOR_JGPOWER_str  = toString  (cur_leftPower = int((LY/LY_MAX) * (RIGHT_MOTOR_JGPOWER_MAX)  +  (LX/LX_MAX) * (LEFT_MOTOR_JGPOWER_MAX)));

        if(magnitude > LEFT_THUMB_DEADZONE){ // then we want to consider what it does
            if(magnitude > THUMB_MAX) // max thumbing
                magnitude = THUMB_MAX;

            // make sure the magnitude is the actual magnitude of that i need to consider
            magnitude -= LEFT_THUMB_DEADZONE;
            normalizedMagnitude = magnitude/(THUMB_MAX - LEFT_THUMB_DEADZONE);    // this is a percentage of the possible strength of the magnitude

            // RIGHT MOTOR TEST WITH MAGNITUDE OF THUMB STICK MOVEMENT (NOT NEEDED ANYMORE.. USING COMPONENTS LX and LY to DETERMINE MOVEMENT.
            //RIGHT_MOTOR_JGPOWER_str = toString(RIGHT_MOTOR_JGPOWER_MAX * normalizedMagnitude);
            //cout << RIGHT_MOTOR_JGPOWER_str << endl;
            //cout << g.commandValue("MG @ABS[-2.37]; MG " + RIGHT_MOTOR_JGPOWER_str + ";") << endl;
        }
        else{
            magnitude = 0;
            normalizedMagnitude = 0;
        }// end DEADZONE CHECK

        // now i can send the motor commands accordingly
        // if the power to left or right is different then send it to galil.. else dont send anything:
        if((cur_rightPower != prev_rightPower) || (cur_leftPower != cur_leftPower)){
            dresult = g->commandValue("JG " + LEFT_MOTOR_JGPOWER_str + "," + RIGHT_MOTOR_JGPOWER_str + ";");
            cout << "JG " + LEFT_MOTOR_JGPOWER_str + "," + RIGHT_MOTOR_JGPOWER_str + ";" << endl;
        }
        prev_leftPower = cur_leftPower;
        prev_rightPower = cur_rightPower;

        if(STOP_MOTION == true){
            break;
        }

    }// end while

    g->commandValue("ST;");
    cout << "STOPPING... no longer controlling IGV" << endl;
    return true;
}
/****************************   ******/
/**    END command_IGV    **/
/****************************   ******/



/* W A S D control and SPACE is to STOP */
/****************************                        ******/
/**     Begin Control of IGV with KEYBOARD    **/
/****************************                        ******/
void
control_IGV_with_KEYBOARD(Galil* &g){


  // LEFT_THUMB_DEADZONE; // experiemental value(anywhere from 0-65534)
  // GALIL SPECS:
  string RIGHT_MOTOR_JGPOWER_str = "";
  string LEFT_MOTOR_JGPOWER_str = "";

  int RIGHT_MOTOR_ACCELERATION  =   25000;
  int RIGHT_MOTOR_DECCELERATION =   45000;
  int RIGHT_MOTOR_JGPOWER_MAX   =   55000;  //definitely should not use that..

	int CRUISE_JG_SPEED 					= 	25000; // for cruising around

  int LEFT_MOTOR_ACCELERATION   =   RIGHT_MOTOR_ACCELERATION;
  int LEFT_MOTOR_DECCELERATION  =   RIGHT_MOTOR_DECCELERATION;
  int LEFT_MOTOR_JGPOWER_MAX    =   RIGHT_MOTOR_JGPOWER_MAX;

  g->commandValue("AC ," + toString(RIGHT_MOTOR_ACCELERATION) + "; "
               + "DC ," + toString(RIGHT_MOTOR_DECCELERATION) + "; "
              + "JG 0,0;");

  g->commandValue("BG;");   // BEGIN THE GALIL EXECUTION


  float LX;
  float LY;
  float magnitude;
  float normalizedLX;
  float normalizedLY;
  float normalizedMagnitude;

  int cur_rightPower  = 0;
  int cur_leftPower   = 0;
  int prev_rightPower = 0;
  int prev_leftPower  = 0;

	int command_isrunning = 0;

  while(!GetAsyncKeyState(VK_ESCAPE)){
		
						// GO FORWARD!
		if(GetAsyncKeyState((int)W_key)){
			LEFT_MOTOR_JGPOWER_str = toString(CRUISE_JG_SPEED);
			RIGHT_MOTOR_JGPOWER_str = toString(CRUISE_JG_SPEED);
			command_isrunning = W_key;
		}
		else if(GetAsyncKeyState((int)A_key)){ 										// GO LEFT
			LEFT_MOTOR_JGPOWER_str = toString(0);
			RIGHT_MOTOR_JGPOWER_str = toString(CRUISE_JG_SPEED);
			command_isrunning = A_key;
		}
		else if(GetAsyncKeyState((int)S_key)){
			LEFT_MOTOR_JGPOWER_str = toString(-1 * CRUISE_JG_SPEED);	// GO BACK
			RIGHT_MOTOR_JGPOWER_str = toString(-1 * CRUISE_JG_SPEED);
			command_isrunning = S_key;
		}
		else if(GetAsyncKeyState((int)D_key)){
			LEFT_MOTOR_JGPOWER_str = toString(CRUISE_JG_SPEED);			// GO RIGHT
			RIGHT_MOTOR_JGPOWER_str = toString(0);
			command_isrunning =	D_key;
		}
		else if(GetAsyncKeyState(VK_SPACE)){
			LEFT_MOTOR_JGPOWER_str = toString(0);			// GO RIGHT
			RIGHT_MOTOR_JGPOWER_str = toString(0);
			command_isrunning =	0;
		}

    if((command_isrunning != prev_rightPower) || (command_isrunning != cur_leftPower)){
      g->commandValue("JG " + LEFT_MOTOR_JGPOWER_str + "," + RIGHT_MOTOR_JGPOWER_str + ";");
      cout << "JG " + LEFT_MOTOR_JGPOWER_str + "," + RIGHT_MOTOR_JGPOWER_str + ";" << endl;

    }
		
			prev_rightPower = command_isrunning;
			prev_leftPower = command_isrunning;

		Sleep(100);

  }// end while

  g->commandValue("ST;");   // STOP
  cout << "no longer controlling IGV" << endl;
  return;
}