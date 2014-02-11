/* game.h
 *
 *      Represents the game.
 *
 */


#include "player.h" // also includes the std libs and angel.h through geometry.h
#include "npc.h"    // includes:  character
#include "maze.h"   // includes:  floor, sphere, terrain, wall, windmill
#include "camera.h" // includes:  geometry
 


#ifndef GAME_H
#define GAME_H

#define WINDOW_TITLE_PREFIX "Maze"
#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 800

#define WindowPosX 500
#define WindowPosY 50

#define WM(w) ((Windmill*)w)    // easy type cast to windmill from geometry
#define PLAYER(p) ((Player*)p)  // easy type cast to windmill from geometry



class Game {
private:

     int light_on;
     
    GLuint program_id;

    int CurrentWidth,
        CurrentHeight, 
        WindowHandle;

    Camera*     cam;             // the camera description object
    Geometry*   player;
    // Plane*      plane;

    Terrain*    terrain;
    Geometry*   windmill;
    vector<Geometry*>   windmills;
    Maze* maze;

    Geometry**  game_objects;   // not sure what im doing with this yet...


    char PREV_KEY;

    bool W_IS_PRESSED; // pitch down
    bool A_IS_PRESSED; // roll left
    bool S_IS_PRESSED;
    bool D_IS_PRESSED;

    bool Q_IS_PRESSED;  //yaw left
    bool E_IS_PRESSED; 

    bool LEFT_IS_PRESSED;
    bool RIGHT_IS_PRESSED;
    bool UP_IS_PRESSED;
    bool DOWN_IS_PRESSED;

    int  currentMouseX;
    int  currentMouseY;


    /*
       Because GLUT expects C-style functions to be used with its callback
       mechanism, wrappers are needed in order to register a member function.
       So, we store a pointer to the object to call the member functions on
       in callbackInstance. Then we have some simple static class functions to
       register with GLUT, which will call the corresponding member function on
       the object pointed to by callbackInstance.
    */
    static Game* callbackInstance;
    static void displayWrapper();
    static void resizeWrapper(int, int);
    static void keyboardWrapper(unsigned char, int, int);
    static void specialKeysWrapper(int, int, int);

    static void keyboardUpWrapper(unsigned char key,int x, int y);
    static void specialKeysUpWrapper(int, int, int );

    static void timerFuncWrapper(int);
    static void idleFuncWrapper(void);
    static void closeCleanupWrapper(void);
   
    static void mouseWrapper(int button, int state, int x, int y);
    static void mouseMotionFuncWrapper(int x, int y);
    // add more callback wrappers as needed 

    // more member variables here...

    /*
       The default c'tor is private because so command-line args passed in.
    */
    Game();
    bool collide(Geometry* obj1, Geometry* obj2);
    /*
       Initialization for GLUT and OpenGL. Takes command-line arguments
       and passes them on to GLUT.
    */
    void   glut_initialize(int*, char**);

    
    /*
       Registers our static wrapper callbacks with GLUT.
    */
    void registerCallbacks();

    /*
       Below are the "real" callback functions. These are the ones that
       provide the functionality of the callbacks.
    */
    void display();
    void resize(int, int);
    void keyboard(unsigned char, int, int);
    void specialKeys(int, int, int );
    void keyboardUp(unsigned char key,int x, int y);
    void specialKeysUp(int, int, int );

    void timerFunc(int);
    void idleFunc(void);
    void closeCleanup(void);

    void mouse(int button, int state, int x, int y);
    void getMousePos(int *, int *);
    void mouseMotionFunc(int x, int y);
    /*
       Initializes the actual game stuff.
    */
    void initGame();

    // Add private game functions here...


public:




    /*

       C'tor that takes command-line arguments, so it can pass them onto GLUT.
    */
    Game(int*, char**);

    /*
       Default d'tor.
    */
    ~Game();

    /*
       Initialization and starts the game, i.e. enters the GLUT main loop.
    */
    void run();

    // Public game functions here...

};

#endif
