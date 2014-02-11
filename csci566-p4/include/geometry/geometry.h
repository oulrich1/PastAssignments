/* Geometry.h
 *
 * Base class for geometric objects.
 */

#include "utils.h"

using namespace std;

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

#ifndef GEOMETRY_H
#define GEOMETRY_H

 // this is the length of one symetric side of the unit cube..
// #define UNIT_CUBE_D     0.5
#define UNIT_CUBE_D     1.0

// this is half the length in usable coordinates when plotting cube points         
#define U_CUBE_C        UNIT_CUBE_D/2




#define toRadians(degrees) (degrees * DegreesToRadians)


class Geometry {

public:
    Geometry();
    Geometry(GLuint _program_id);

    void constrict_angles();

    virtual ~Geometry();

        /* generates triangles for gl.. from the verticies */
    static vec4*    glquad( vec4 *cur_vertices, int a, int b, int c, int d );
    static vec4*    glcube( vec4 *verts );

        /* generates verticies.. */
    static vec4*    createUnitTriangle();
    static vec4*    createUnitPlane();
    static vec4*    createUnitCube();
    static vec4*    createUnitSphere();
    
    static vec4*    createUnitColors(); // 8 points colored in order..

    /*
         Pure virtual function to display the Geometry. Classes
         inheriting from Geometry need to provide a definition
         for display().
    */
    virtual void init_data() = 0;   // initializes this object's data
    virtual void init_gl() = 0;        // initializes the GPU 
                                    // with any data we care about sending over
    virtual void display() = 0;     // switches to the object's vao/vbo and 
                                    // invokes postRedisplay

    // rotates the entire body by radians
    //  virtual void rotate(float rad) = 0;

    void    rotate(vec4 ); // rotates...
    void    translate(vec4 );   // translates

    // offset is vector, eye is point
    // not goign to make getters for these..
    point4      eye;
    point4      at;
    vec4        up;

    vec4    getDirection(){return direction;}
    void    setDirection(vec4 v){direction = v;}

    int     getRoomIndex();
    void    setRoomIndex(int index);

    float   radius;
    //TODO:
    // virtual void collides(Geometry *) = 0;

protected:
    /* GL SPECIFIC  ATTRIBUTES */

    GLuint  program_id,   // shader program id
            vao,          // vertex  array object id
            vbo,          // vertex buffer object id
            ibo,           // index  buffer object id
            texture_id;

    // model-view matrix uniform shader variable location
    GLuint  model_view;  
    GLuint  texture_pos;

    char *  texture_image;  //TODO: 

    /* colro uniform variable location */
    GLuint new_color;

    GLuint normalMatrixLoc,
            lightLoc,
            addAmbientLoc,
            addDiffuseLoc,
            addSpecularLoc;


    GLintptr TOTAL_BUFFER_OFFSET;

    GLintptr VERTEX_BUFFER_OFFSET;
    GLintptr COLOR_BUFFER_OFFSET;
    GLintptr TEXTURE_BUFFER_OFFSET;

    /* END GL SPECIFIC STUFF */


    int     room_index;

    // BEGIN GEOMETRY LOGIC STUFF
       
    int     NUM_COMPONENTS;  // number of components that need a matrix
    mat4*   model_view_matricies; 
    mat4*   models;   
    mat4*   views;


    vec4    offset; // offsets this instance in 3d space



    /* ---------------- */

    mat4    I;
    vec4    thetas;
    vec4    direction;

    

    /* orientation properties */
    float   theta_x;        /// using these and NOT yaw ptich roll...
    float   theta_z;
    float   theta_y;

    // default movement rate:
    float dx = 0.01, dy = 0.01, dz = 0.01;

    // default rotate rate:
    float dTheta = 4.5, dPhi = 0.5;

    // dmovement of geometry through the medium
    float   drag_factor;

private:


        // common state variables
    

};




#endif
