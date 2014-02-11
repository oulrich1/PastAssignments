#include "world_object.h"

/* Note: these walls are always vertical.
    They can be projected onto the xz plane and
    they will form a line..  */

#ifndef WALL_H
#define WALL_H 


struct point
{
    float x;
    float y;
    float z;

    float height;
};


/*  contains properties that are 
    common to all instances of walls */
class WallProperties
{
public:
    WallProperties(){
    
        vec4* vertices          = Geometry::createUnitCube();
        vec4* _glcubevertices   = Geometry::glcube(vertices);

        vec4* colors            = Geometry::createUnitColors();
        vec4* _glcubecolors     = Geometry::glcube(colors);

        for (int iter = 0; iter < PTS_N_CUBE; ++iter){
            cube_vertices[iter] = vertices[iter];
            cube_colors[iter] = colors[iter];
        }
        
        for (int iter = 0; iter < 36; ++iter){
            glcubevertices[iter] = _glcubevertices[iter];
            glcubecolors[iter] = _glcubecolors[iter];
        }

        /* delete the generated vertecies.. 
         They are stored in this properties class */
        delete vertices;
        vertices = NULL;

        delete colors;
        colors = NULL;
        
    }
    ~WallProperties(){ }

// private:
    vec4    cube_vertices[PTS_N_CUBE];
    vec4    cube_colors[PTS_N_CUBE];

    vec4    glcubevertices[36];
    vec4    glcubecolors[36];
};



class Wall : public Geometry
{

public:
    Wall(GLuint _program_id, vec4 _room_origin, float width, float height = 200);
    ~Wall();

                                    // with any data we care about sending over
    /*virtual*/ void display();   

    point   getStart();
    point   getEnd();

    float   getWidth(){return average_width;}

    // given this Wall type's wall height and width along with these params
    // it will create a new wall_instance_matrix.. 
    // on display, all wall instances are drawn 
    void pushInstance(vec3 trans, vec3 scale, vec3 rot);

    static WallProperties wall_properties;
    

private:

    void init_logic(float width, float height);
    /*virtual*/ void init_data();   // initializes this object's data
    /*virtual*/ void init_gl();        // initializes the GPU 

    void init_models();
    void init_views();

    
    std::vector<mat4> wall_instance_matrices;


    vec4 room_origin; // origin of this room in the world frame
    point start;
    point end;


    vec4 direction;

    float average_height;
    float average_width;


    int VERTEX_COUNT;

    // TODO: Geometry should contain Model Geometry and GL Geometry

    // these are gl geometries
    vec4* points;   
    vec4* colors;
    vec2* tex_coords;


    /* wrap into texture class */
    GLuint  textures[1];

    static const int  TextureSize  = 256;
    GLubyte cobblestone_ground[TextureSize][TextureSize][3];
    /* - - - - - - - - - - - - */


};



#endif