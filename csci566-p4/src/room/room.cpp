#include "room.h"

Room::Room(GLuint _program_id, vec4 _offset) : Geometry(_program_id){
	float dummy_width = 100;
	float dummy_length = 150;

    offset = _offset;

    /* initialize the state logic of this room: collisions, geometry*/
	init_logic(dummy_width, dummy_length);

    /* convert the model geometry into usable vertecies for the gpu */
    init_data();

    /*send the vertecies to the gpu,  among other things*/
    init_gl();
}

Room::Room(GLuint _program_id, std::vector<pointpair>& wall_points, 
                vec4 _offset, float _width, float _length) : Geometry(_program_id){

    offset = _offset;
    
    this->wall_points = wall_points;

    /* initialize the state logic of this room: collisions, geometry*/
    init_logic(_width, _length);

    /* convert the model geometry into usable vertecies for the gpu */
    init_data();

    /*send the vertecies to the gpu,  among other things*/
    init_gl();
}

Room::~Room(){
    // clean up
    for (int i = 0; i < width; ++i){
        delete is_blocked[i];
    }
    delete is_blocked;

    // remove the walls
    for (int i = 0; i < walls.size(); ++i){
        delete walls[i];
    }
}

/* HELPER CONSTRUCTOR: Initializes the room attributes:
    number of walls, width of the walls, the collision field.. 
     then it sets up the walls themselves and any other objects.. */
void Room::init_logic(float _width, float _length){
    width = _width;
    length = _length;


    /* used for wall collision detection: */
    is_blocked = new bool*[(int)width + 1];
    for (int i = 0; i < width; ++i){
        is_blocked[i] = new bool[(int)length + 1];
        for (int j = 0; j < length; ++j){
            is_blocked[i][j] = false;
        }
    }

    /* initialize floor */
    vec4 theFloorOffset = vec4(this->offset);  // same as the room..
    theFloor = new Floor(program_id, theFloorOffset, width, length);

    /* initialize walls */

    number_of_walls = 2;

    //float wall_length = 400;
    float wall_height = 200;
    float wall_width = 10;
    hallway_width = 100;

    vec4 wall_offset = vec4(this->offset);
    // initialize a wall type..
    walls.push_back( new Wall(program_id, wall_offset, wall_width, wall_height));

    /* this is pretty messy: TODO: maze should be the one
            to specify wall endpoints.. and pass a list of enpoints to a room.
            The room should look at those endpoints and create instances for \
            each one of those segments

            tldr: RATHER than hardcoding walls in a room.. Could use line segments &
                    wall properties to specify walls */

    /* New Way */
        // wall_points segments
    vec4 p2;
    vec4 p1;
    int num_wall_points = wall_points.size();
    for (int i = 0; i < num_wall_points; ++i) {
        p2 = wall_points[i].p2;
        p1 = wall_points[i].p1;

        // cout << "p2: " << p2 << endl;
        // cout << "p1: " << p1 << endl;
        
        // vector to center of segment..
        vec4 translation_to_center = ((p2 - p1)/2) + p1;
        vec3 translate = vec3(  translation_to_center.x, 
                                translation_to_center.y, 
                                translation_to_center.z); //remember, centered at origin..

        // x: measurable. height: constant, width: constant
        vec3 scale = vec3(Angel::length(p2-p1), wall_height, wall_width);

        // calculate rotation about the y...
        float d_xx = (p2.x - p1.x);
        float d_zz = (p2.z - p1.z);
        if (d_xx < 0 && d_zz > 0){  
            d_xx = abs(d_xx);
        }

        float r_xy = Angel::length(p2-p1); 
        vec3 rotate = vec3(0,(acos(d_xx/r_xy)/DegreesToRadians),0);

        // cout << translate << " " << scale << " " << rotate << endl;
        walls[0]->pushInstance(translate, scale, rotate);
    }
}

void Room::init_data(){
    // initalize the data that we are going to need
    // to send to the GPU, later init_gl is called..
    // that sends el gl data to el gpu
}
void Room::init_gl(){
    // set up the vao and vbo stuff:
    // send to GPU, and make sure variables in shader are .. 
    // initilized..enabled..properly
}

/* Update the GPU with the model/view matricies if they changed 
    and then call display on stuff */
void Room::display(){
    //display the floor
    theFloor->display();

    //for all walls and geometries.. display those!
    for (int i = 0; i < walls.size(); ++i){
        walls[i]->display();
    }
    // for (int i = 0; i < geometries.size(); ++i)
    // {
    //     geometries[i]->display();
    // }
}

void Room::attach_generic_geometry(Geometry* g){
    /* this gets tricky: ideally the geometry is organized spacially..
        NOT IDEAL: */
    // a vector of geometries for this room
    //geometries.push_back(g) ;
}


