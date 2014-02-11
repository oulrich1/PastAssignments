/* game.cpp
 *
 * Implementation of Game class.
 *
 */

#include "Angel.h"
#include "game.h"
 
#include <cstdlib>
#include <GL/glut.h>

// static initializer
Game* Game::callbackInstance(NULL);

Game::Game() {

}

Game::Game(int* argcp, char** argv) {
    PREV_KEY = ' ';
    W_IS_PRESSED = false;
    A_IS_PRESSED = false;
    S_IS_PRESSED = false;
    D_IS_PRESSED = false;
    Q_IS_PRESSED = false;
    E_IS_PRESSED = false;

    LEFT_IS_PRESSED = false;
    RIGHT_IS_PRESSED = false;
    UP_IS_PRESSED = false;
    DOWN_IS_PRESSED = false;

    light_on = 1;

    printf("Creating instance of game\n"); 

    glut_initialize(argcp, argv);       //initializes the window and display..

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

Game::~Game() {
    // do any cleanup
}

void Game::glut_initialize(int* argcp, char** argvp) {
    // GLUT init code here...
    GLenum GlewInitResult;
     CurrentWidth = WINDOW_WIDTH;
     CurrentHeight = WINDOW_HEIGHT;

    /*  - - - - - - -  */
    glutInit(argcp, argvp);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(CurrentWidth, CurrentHeight);
    glutInitWindowPosition(WindowPosX, WindowPosY);
    glutInitContextVersion(4, 2);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );
    
    WindowHandle = 0;
    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

    if(WindowHandle < 1) {
        fprintf(
            stderr,
            "ERROR: Could not create a new rendering window.\n"
        );
        exit(EXIT_FAILURE);
    }


    // event handlers are set when the game is run..

    /*  - - - - - - -  */

    glewExperimental = GL_TRUE;
    GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult) {
        fprintf(
            stderr,
            "ERROR: %s\n",
            glewGetErrorString(GlewInitResult)
        );
        exit(EXIT_FAILURE);
    }
    
    
    fprintf(
        stdout,
        "   INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
    );


    glutSetCursor(GLUT_CURSOR_INHERIT);  //GLUT_CURSOR_INHERIT, GLUT_CURSOR_NONE
    glutWarpPointer(CurrentWidth/2, CurrentHeight/2); //for every frame as well
 

    printf("\n0.) Initialized: GLUT\n");

}




/* --------------------------------------------------------------------------   */
/* CaLLBACK FUNCTIONS: hopefulling listed in the order that they were registred */


/* Render!!! just tell the objects to display their data!! */
void Game::display() {
    // // display code here...

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        /* call draw arrays for each of the vbo's */
        windmill->display();

        for (int i = 0; i < windmills.size(); ++i){
            WM(windmills[i])->display();
        }

    // this should be done only once on init...
    // this is here just for reference.. 
    

    maze->display();
    #ifdef ENABLE_TERRAIN
        terrain->display();
    #endif
    
    glutSwapBuffers();   // swap double buffers
    glutPostRedisplay(); // mark the window to be redrawn
}

void Game::displayWrapper() {
    callbackInstance->display();
}



void Game::resize(int width, int height) {
    // resize code here...
    CurrentWidth = width;
    CurrentHeight = height;

    cam->aspect = GLfloat(width)/height;
    cam->update_proj();   

    glutInitWindowSize(CurrentWidth, CurrentHeight);
    glViewport(0, 0, CurrentWidth, CurrentHeight);
    glutPostRedisplay();
}

void Game::resizeWrapper(int width, int height) {
    callbackInstance->resize(width, height);
}




void Game::keyboard(unsigned char key, int x, int y) {
      // keyboard code here...


    switch( key ) {
    case 033: // Escape Key
    case '!':
        exit( EXIT_SUCCESS );
        break;

    case 'o':  
        WM(windmill)->rotate(toRadians(10));
        for (int i = 0; i < windmills.size(); ++i){
            WM(windmills[i])->rotate(toRadians(5));
        }
    break;
    case 'O':
        WM(windmill)->rotate(toRadians(-10));
        for (int i = 0; i < windmills.size(); ++i){
            WM(windmills[i])->rotate(toRadians(-5));
        }
    break;
    case 'p': {
        // start/stop windmill turning
        uint wm_mode = WM(windmill)->switch_mode();    

        for (int i = 0; i < windmills.size(); ++i){
            WM(windmills[i])->switch_mode();
        }

        if(wm_mode == WindmillMode::OFF){
            printf("Windmill Mode Off\n");
        } else {
            printf("Windmill Mode On\n");
        }
        break;
    }
    case 'P': {
        // start/stop windmill turning
        int wm_direction = WM(windmill)->switch_turbine_direction();   
        for (int i = 0; i < windmills.size(); ++i){
            WM(windmills[i])->switch_turbine_direction();
        } 
        if(wm_direction == 1){
            printf("Windmill rotating CW\n");
        } else {
            printf("Windmill rotating CCW\n");
        }
        break;
    }
    case 't': {
        
        break;
    }
    case 'T': {
        
        break;
    }

    /* plane controls: forward,backward, strafe: sides: left,right */
    case 'w': {
        //cam->walk(vec4(0,0,-1,0));
        
        W_IS_PRESSED = true;
        break;
    }
    case 'a': {
        PLAYER(player)->setControlState(Player::STRAFE_LEFT);
        A_IS_PRESSED = true;
        break;
    }
    case 's': {
       
       S_IS_PRESSED = true;
        break;
    }
    case 'd': {
       PLAYER(player)->setControlState(Player::STRAFE_RIGHT);
       D_IS_PRESSED = true;
        break;
    }

    /* plane controls : strafe UP/DOWN */
    case 'x': {
       
        break;
    }
    case 'z': {
       
        break;
    }
    case '1':
    case 'l': {
        maze->trigger_lighting();
        break;
    }

    /* player control: TILT HEAD */
    case 'q': {
        PLAYER(player)->setControlState(Player::ROLL_LEFT);
        Q_IS_PRESSED = true;
        break;
    }
    case 'e': {
        PLAYER(player)->setControlState(Player::ROLL_RIGHT);
        E_IS_PRESSED = true;
        break;
    }
    case '[': {  // reset values to their defaults
        // WM(windmill)->init();
        // for (int i = 0; i < windmills.size(); ++i){
        //     WM(windmills[i])->init();
        // }
        break;
    }
    case ' ':
        //plane->resetOrientation();
        break;
    }

}

void Game::keyboardWrapper(unsigned char keycode, int x, int y) {
    callbackInstance->keyboard(keycode, x, y);
}


void Game::specialKeys(int key, int x, int y) {
    if (glutGetModifiers() == GLUT_ACTIVE_SHIFT){
        PLAYER(player)->setRunSpeedMultiplier(3); // run 3 times as fast
    } else {
        PLAYER(player)->setRunSpeedMultiplier(1);
    }

    switch( key ) {
        case GLUT_KEY_LEFT: {
            PLAYER(player)->setControlState(Player::YAW_LEFT);
            LEFT_IS_PRESSED = true;
            break;
        }
        case GLUT_KEY_RIGHT: {
            PLAYER(player)->setControlState(Player::YAW_RIGHT);
            RIGHT_IS_PRESSED = true;
            break;
        }
        case GLUT_KEY_UP: {

            PLAYER(player)->setControlState(Player::MOVE_FORWARD);
            UP_IS_PRESSED = true;
            break;
        }
        case GLUT_KEY_DOWN: {
            PLAYER(player)->setControlState(Player::MOVE_BACKWARD);
            DOWN_IS_PRESSED = true; 
            break;
        }

    }

}

void Game::specialKeysWrapper(int keycode, int x, int y){
    callbackInstance->specialKeys(keycode, x, y);
}



void Game::keyboardUp(unsigned char key, int x, int y){
    switch( key ) {
        /* plane controls : ROLL and PITCH */
        case 'w': {
            
            W_IS_PRESSED = false;
            break;
        }
        case 'a': {
            PLAYER(player)->unsetControlState(Player::STRAFE_LEFT);
            A_IS_PRESSED = false;
            break;
        }
        case 's': {
            
            S_IS_PRESSED = false;
            break;
        }
        case 'd': {
            PLAYER(player)->unsetControlState(Player::STRAFE_RIGHT);
            D_IS_PRESSED = false;
            break;
        } 

        /* player control: TILT HEAD */
        case 'q':{
            PLAYER(player)->unsetControlState(Player::ROLL_LEFT);
            Q_IS_PRESSED = false;
            break;
        }
        case 'e':{
            PLAYER(player)->unsetControlState(Player::ROLL_RIGHT);
            E_IS_PRESSED = false;
        }

    }
}

void Game::keyboardUpWrapper(unsigned char key,int x, int y){
    callbackInstance->keyboardUp(key, x, y);
}



void Game::specialKeysUp(int key, int x, int y){
    switch( key ) {
        /* plane controls : ROLL and PITCH */
        case GLUT_KEY_LEFT: {
            PLAYER(player)->unsetControlState(Player::YAW_LEFT);
            LEFT_IS_PRESSED = false;
            break;
        }
        case GLUT_KEY_RIGHT: {
            PLAYER(player)->unsetControlState(Player::YAW_RIGHT);
            RIGHT_IS_PRESSED = false;
            break;
        }
        case GLUT_KEY_UP: {
            PLAYER(player)->unsetControlState(Player::MOVE_FORWARD);
            UP_IS_PRESSED = false;
            break;
        }
        case GLUT_KEY_DOWN: {
            PLAYER(player)->unsetControlState(Player::MOVE_BACKWARD);
            DOWN_IS_PRESSED = false; 
            break;
        }

    }
}

void Game::specialKeysUpWrapper(int key, int x, int y){
    callbackInstance->specialKeysUp(key, x, y);
}




/* MOUSE CALLBACKS */
void Game::mouse(int button, int state, int x, int y){
    
}

void Game::mouseWrapper(int button, int state, int x, int y){
    callbackInstance->mouse(button, state, x, y);
}


void Game::mouseMotionFunc(int x, int y){
    currentMouseX = x;
    currentMouseY = y;
    //printf("%d %d\n", x, y);
    //paddle->set_position(vec2( ((2.0*x)/CurrentWidth - 0.82) ,  ((-2.0*y)/CurrentHeight) + 1.76) );
}

void Game::mouseMotionFuncWrapper(int x, int y){
    callbackInstance->mouseMotionFunc(x, y);
}
/* - - END - - - - - - MOUSE CALLBACKS */


void Game::getMousePos(int *mouseX, int *mouseY){
    *mouseX = currentMouseX;
    *mouseY = currentMouseY;
}


/* used to perform animations:
    modify the data within the objects.. */
void Game::timerFunc(int value){
    const float mouseSensitivity = 0.05; (void)mouseSensitivity;
    int mouseX, mouseY;
    getMousePos(&mouseX, &mouseY);
    mouseX = mouseX - CurrentWidth/2;
    mouseY = mouseY - CurrentHeight/2;

   

    WM(windmill)->tick();   // calcuate next position (if relevant)

    for (int i = 0; i < windmills.size(); ++i){
        WM(windmills[i])->tick();
    }

    PLAYER(player)->tick(); // updates it's position given 
                            // the current state it is in


    maze->tick();   // calculate interactions in maze, including collisions.

    cam->tick();

    // if(plane->collided()){
    //     cout << "Collided with the ground" << endl; //or about to..
    // }

    //cout << plane->throttleMessage() << endl;

    // perform animations and calculations regarding animations here
    glutPostRedisplay();
}


void Game::timerFuncWrapper(int value){
    callbackInstance->timerFunc(value);

   
    glutTimerFunc(16, timerFuncWrapper, ++value);
    
}


/* Possibly perform calculations here.. */
void Game::idleFunc(void){
    //glutPostRedisplay();
}

void Game::idleFuncWrapper(void){
    callbackInstance->idleFunc();
}





void Game::closeCleanup(void){
    // clean up stuff when window is closed..
    // call this's destructor..
}

void Game::closeCleanupWrapper(void){
    callbackInstance->closeCleanup();
}

/* -------------------------------------------------- */

void Game::initGame() {
    if (callbackInstance == NULL)     {
        callbackInstance = this;
    }   

    /* - - - - - - - - - - - - - - - - - - - - */
    /*      Shader init                        */

        // member variable "program_id"
    program_id = InitShader( SHADER_PATH("shader_vertex_generic.glsl"), 
                             SHADER_PATH("shader_fragment_generic.glsl") );
    glUseProgram( program_id );



    printf("1.) Initialized: Shaders\n");


    /* - - - - - - - - - - - - - - - - - - - - */
    /*      game init code ...             */

    cam = new Camera(program_id);
    player = (Geometry*) new Player();
    cam->attach(player);    
                            // when something todo with the player changes..
                            // the camera will update with what ever its attached to
                            // if the thing the cam is attached to is NULL.. 
                            // then use default god-cam mode.. keep track of position

    maze = new Maze(program_id);
    maze->attach_player_geometry(player);  // now the maze knows about the player and can 
                                    // process any interactions/collisions between
                                    // all other geometry in the maze.

    #ifdef ENABLE_TERRAIN
    terrain = new Terrain(program_id);
    #endif

    windmill = new Windmill(program_id); 
    uint wm_mode = WM(windmill)->switch_mode(); 
    (void) wm_mode;
    
    windmills = std::vector<Geometry*>(100, NULL);  

    /* Assign windmills to random positions */
    srand(time(NULL));
    for(int i = 0; i < windmills.size(); i++){
        float x, y, z;
        x = rand_f(); 
        z = rand_f(); 
        y = rand_f();

        float domain_interval = 
        #ifdef ENABLE_TERRAIN
            terrain->width - terrain->width/2;
        y = terrain->getHeightAt(x, z);
        #else
            200;
        #endif

        x = x * domain_interval;
        z = z * domain_interval;
        
        vec4 offset = vec4(x, y + rand_f()*2 - 1, z, 0);
        // vec4 offset = vec4(x, y, z, 0);
        #ifdef WINDMILL_DEBUG
            cout << "Offset: " << offset << endl;
        #endif
        windmills[i] = new Windmill(program_id, offset);
    }

    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable( GL_DEPTH_TEST );
    glClearColor((float)135/255, (float)206/255, (float)250/255, 1.0 ); 
    
    printf("2.) Initialized: Game Objects\n");
}

/* -------------------------------------------------  */


// void glutKeyboardUpFunc(void (*func)(unsigned char key,int x,int y)); 
// void glutSpecialUpFunc(void (*func)(int key,int x, int y)); 

/* regeisters the glut callbacks.. */
void Game::registerCallbacks() {
    glutDisplayFunc(displayWrapper);        // calls PostRedisplay
    glutReshapeFunc(resizeWrapper);         // inits the window when window is modified
    glutKeyboardFunc(keyboardWrapper);      // keyboard callback
    glutSpecialFunc(specialKeysWrapper);

    glutKeyboardUpFunc(keyboardUpWrapper);
    glutSpecialUpFunc(specialKeysUpWrapper);

    glutMouseFunc(mouseWrapper);
    glutPassiveMotionFunc(mouseMotionFuncWrapper);

    glutTimerFunc(0, timerFuncWrapper, 0);  // timer function callback for animation
    glutIdleFunc(idleFuncWrapper);          // additional calculations

    glutCloseFunc(closeCleanupWrapper);     // on close: cleanup

}



void Game::run() {

    //the glut callbacks depend on this..
    this->initGame();               // sets up the game instance: 


    // now we can register c-style callback functions
    this->registerCallbacks();  
    printf("3.) Initialized: Various Callbacks, including Display()\n\n");
    

    glClearColor((float)135/255, (float)206/255, (float)250/255, 1.0 ); 


    printf("Last.) Running the game..\n");
    glutMainLoop();
    printf("End.) Game end..\n");
}

// game specific functions here...




