/* windmill.h
 *
 * Base class for the windmill
 */

#include "world_object.h"
 

#ifndef WINDMILL_H
#define WINDMILL_H 


 
//#define WINDMILL_DEBUG

enum WindmillMode {
    OFF = 0,
    ON = 1
};

#define TURN_RATE_DEGREES_PER_FRAME 15

class Windmill : public Geometry
{
    

    /* PUBLIC */
public:
    Windmill(GLuint _program_id, vec4 _offset = vec4(0,0,0,0));
    ~Windmill();
    
    void    init();

    // one iteration or "tick" for a windmill.. 
    // called within timer func in applcation
    void    tick();
    void    display();               // engages the gpu to display the primatives

    uint    switch_mode();                 // switch the state, on or off
                                        // returns current state
    int     switch_turbine_direction();    // returns current direction 

    void    rotate(float rad); // rotates the entire body by radians
    void    turn_blades(float rad);    //turns the blades as a whole (4 total)

    uint    collides(Geometry* collidable);


    /* PRIVATE */
private:

    /* helpers */
            /* These helpers are from Angel's example code */
    void    quad( int a, int b, int c, int d );
    void    colorcube();

    void    init_logic();
    void    init_data();
    void    init_gl();

    void    init_models();
    void    init_views();


    void    update_mv_matricies();
    void    rotate(vec4 direction);
    void    translate(vec4 direction);

    int     Index = 0;

    int NumWindmillComponents; // 4 blades and 1 stem..


    static const int NumVertices = 36;

    /* Data set for GL to draw with*/
    point4 points[NumVertices]; // from the verticies .. create the points array so GL can parse that array effectively..
    color4 colors[NumVertices];

    /* standard unit cube, with 8 pts */
    point4* vertices;
    color4* vertex_colors;


    // Viewing transformation parameters

    struct {
        float x;
        float y;
        float z;
    } view_angles;

    GLfloat radius = 1.0;   // ??
    GLfloat theta = 0.0;    // horizontal angle
    GLfloat phi = 0.0;      // vertical angle

    const GLfloat  dr = 5.0 * DegreesToRadians;


    /* Windmill logic stuff */ 
    uint    windmill_mode;
    int     windmill_turbine_direction;
    float   current_blade_angle; // degrees

    struct {
        float width;
        float height;
    } blade;

    struct{
        float width;
        float height;
    } post;





};


#endif
