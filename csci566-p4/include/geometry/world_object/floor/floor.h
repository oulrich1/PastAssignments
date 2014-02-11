#include "world_object.h"


#ifndef FLOOR_H
#define FLOOR_H 


class Floor : public Geometry 
{
public:
	Floor(GLuint _program_id, vec4 _offset);
    Floor(GLuint _program_id, vec4 _offset, float width, float length);
	~Floor();

    void display();     // switches to the object's vao/vbo and 
                                    // invokes postRedisplay
    void trigger_lighting(){

        light_on ^= 1;
        glUniform1i(addAmbientLoc, light_on);
        glUniform1i(addDiffuseLoc, light_on);
        glUniform1i(addSpecularLoc, light_on);
    }
	/* data */
private:
    void init_logic(float width, float length);
    void init_data();   // initializes this object's data
    void init_gl();        // initializes the GPU 
                                    // with any data we care about sending over

    void init_models();
    void init_views();

	float x_position;
 	float y_position;
 	float z_position;

    float floor_width;
    float floor_length;

 	int VERTEX_COUNT;

    // TODO: Geometry should contain Model Geometry and GL Geometry

    // these are gl geometries
 	vec4* points; 	// create the points array so GL 
    vec4* colors;
    vec2* tex_coords;

    int light_on;

    /* wrap into texture class */
    // texture_id declared in geometry
    // char *          texture_image;  // 256*256*3  (RGB RAW)

    static const int  TextureSize  = 256;
    GLubyte cobblestone_ground[TextureSize][TextureSize][3];
    // /* - - - - - - - - - - - - */

    // LIGHTING:
    vec3 normals[1];

};


#endif

