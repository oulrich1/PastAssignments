
#include "geometry.h"

using namespace std;

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#ifndef CAMERA_H
#define CAMERA_H 


class Camera
{
private:

    static const int YAW_LEFT = 0x0001;
    static const int YAW_RIGHT = 0x0002;
    static const int ROLL_LEFT = 0x0004;
    static const int ROLL_RIGHT = 0x0008;
    static const int PITCH_DOWN = 0x0010;
    static const int PITCH_UP = 0x0020;

    float ROTATE_FACTOR;

    void        constrict_angles();

    // updates the view matrix with geometry data..
    // and then sends it off to the gpu..
    void        update_view(vec4 _eye, vec4 _at, vec4 _up);

    // keeps track of the orientation of spectate mode..
    // otherwise the player can move around and stuff
    // change to this mode:
    //  cam->attach(Geometry*)
    //  attaches the camera to the geometry (figuratively essentially)
    //  really it should just bind to the position and orientation of the 
    //  geometry
    struct spectator_mode_orientation_state_t{
        int x;
        int y;
        int z;

        float   theta_x;     
        float   theta_z;
        float   theta_y;
    } spectator_mode_orientation_state;

    Geometry*   world_geometry;

public:
    Camera(GLuint program_id);
    ~Camera();

    void        tick();     // updates any logic given the attached geometry..

    Geometry*   attach (Geometry*);

    void        set_at(vec4 _at);
    void        set_up(vec4 _up);



    void        update_proj(); // given the camera properties, send a new matrix to the graphics card
    void        update_view();

    

    GLuint      projection_loc, 
                view_loc;

    mat4        projection_mat4, 
                view_mat4;

    GLfloat     fovy = 50.0;  // Field-of-view in Y direction angle (in degrees)
    GLfloat     aspect = 1.1;       // Viewport aspect ratio
    GLfloat     zNear = 0.5, zFar = 30000.0;

    point4      eye;
    point4      at;
    vec4        up;

    /* camera orientation properties */
    float   theta_x;        /// using these and NOT yaw ptich roll...
    float   theta_z;
    float   theta_y;

    // aka: orient
    void adjust(vec4 direction); // vec4 orientation

    // walk function,
    // increments current position
    // in that direction..........
    // (essentially moves the world)
    void walk(vec4 direction);

    // walk rate:
    float dx = 0.01, dy = 0.01, dz = 0.01;

    // turn function:
    // turns the camera (essentially rotates the world)
    void offsetOrientation(vec2 direction);
    // turn rate:
    float dTheta = 4.5, dPhi = 0.5;

    // might or might not need 
    // to be accessed publicly


};

#endif