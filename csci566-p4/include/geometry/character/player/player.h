#include "character.h"

#ifndef PLANE_H
#define PLANE_H 

#define INCR_THROTTLE_FACTOR 1.51235 //RANDOM!
#define THROTTLE_MAX 200
#define MAX_SPEED    100

#define STRAFE_LEFT_SPEED  190
#define STRAFE_RIGHT_SPEED  190
#define STRAFE_UP_SPEED  190
#define STRAFE_DOWN_SPEED  190
#define MOVE_FORWARD_SPEED  200
#define MOVE_BACKWARD_SPEED  185


class Player : public Geometry
{
public:
    Player();
    ~Player();

    // control masks:
    static const int YAW_LEFT = 0x0001;
    static const int YAW_RIGHT = 0x0002;
    static const int ROLL_LEFT = 0x0004;
    static const int ROLL_RIGHT = 0x0008;
    static const int PITCH_DOWN = 0x0010;
    static const int PITCH_UP = 0x0020;

    static const int STRAFE_LEFT = 0x0040;
    static const int STRAFE_RIGHT = 0x0080;
    static const int STRAFE_UP = 0x0100;
    static const int STRAFE_DOWN = 0x0200;
    static const int MOVE_FORWARD = 0x0400;   //aka move forward
    static const int MOVE_BACKWARD = 0x0800;  //aka move backward



    float ROTATE_FACTOR;

    int     current_control_state;

    /* Updates the Player's position given the 
        current state (that the user had applied 
        on keypress) */
    bool    tick();



    void    set_at(vec4 _at);
    void    set_up(vec4 _up);

    /* update proj and update 
      views are done by the camera */
    void    update_proj();
                            // updates the view matrix for THIS geometry.. 
                            // sends the glUniformMatrix4fv to the GPU
    void    update_view();

    void    init_data();
    void    init_gl(); 
    void    init_models();
    void    init_views();     
    void    display();   
    // void    rotate(vec4 direction);
    // void    translate(vec4 direction);


    bool    pause();
    bool    unpause();

    string  throttleMessage();

    bool    increaseThrottle();
    bool    decreaseThrottle();

    bool    setThrottle(float throttle);
    float   getThrottle();

    float   setRunSpeedMultiplier(float); // returns the previous multiplier


    void    setControlState(int state);
    void    unsetControlState(int state);

    bool    controlStick(vec4);
    bool    controlDirection(vec4); // control the stick in certain direction...

    bool    resetOrientation(vec4 up = vec4(0,1,0,0));
    bool    collided();



    /* - - - - data  - - - - */

    // THROTTLES // 
    // the max the throttle can ever be.. 
    // this determiens accelerations
    float   max_throttle = 100;

    float   cur_throttle = 0;

    float   min_throttle = 0; 




    /* - - - - - - - - - - - */
private:
    GLuint  program_id,   // shader program id
            vao,        // vertex  array object id
            vbo,        // vertex buffer object id
            ibo;        // index  buffer object id

    /* GEOMETRY THAT DEFINES --- PLAYER     */
    /*      standard unit cube, with 8 pts  */
    point4 vertices[PTS_N_CUBE];
    color4 vertex_colors[PTS_N_CUBE];

    static const int NumVertices = 36;
    /* Data set for GL to draw with*/
    point4 points[NumVertices];
    color4 colors[NumVertices];

    bool    player_frozen;

    float   sprint_multiplier = 1;

};

#endif