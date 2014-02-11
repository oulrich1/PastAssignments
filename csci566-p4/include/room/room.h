#include "terrain.h"
#include "windmill.h"

#include "sphere.h"


#include "floor.h"
#include "wall.h"

#ifndef ROOM_H
#define ROOM_H 

/* A room contains a ton of geometry..
   However, a room is also a geometry */
class Room : public Geometry
{
public:
	Room(GLuint _program_id, vec4 _offset);
	Room(GLuint _program_id, std::vector<pointpair>& wall_points, vec4 _offset, float width, float height);
	~Room();   

	void init_logic(float width, float height);
	/*virtual*/ void init_data();   // initializes this object's data
    /*virtual*/ void init_gl();        // initializes the GPU 
                                    // with any data we care about sending over
    /*virtual*/ void display();     // switches to the object's vao/vbo and 
                                    // invokes postRedisplay


	void    attach_generic_geometry(Geometry* g);

    int     getWallTypeCount(){ return walls.size(); }
    float   getWallWidthFromWallTypeIndex(int index){ return walls[index]->getWidth(); }

    void trigger_lighting(){theFloor->trigger_lighting();}

private:

	float width;
    float length;
    float height;

    int   number_of_walls;
    
    float hallway_width;

    /* used for collision detection */
    bool** is_blocked;
    
    Floor*                  theFloor;
    std::vector<Wall*>      walls;
    std::vector<pointpair>  wall_points;
    //std::vector<Geometry*> geometries;
};

#endif
