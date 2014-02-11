#include "maze.h"

Maze::Maze(GLuint _program_id){
    program_id = _program_id;

    width = 2000;
    length = 2000;
    height = 0;

    // initialize room and MAZE offset..
    x_position  = -1000;
    y_position  = 0;
    z_position  = 1000;


    // TODO: WRAP THESE INTO MODULES/ROOMs

    // JUST REALIZED that the y position are off for all these walls..
    // (oh well.. )

    /* create the walls and the map (for collision detection) */
    // std::vector<pointpair> wall_points; //decalred in class

    // segments are relative to the room offset
    vec4 start_segment = vec4(0,0,-10,0);
    vec4 end_segment = vec4(1000,0,-10,0);
    wall_points.push_back({start_segment, end_segment});


    // OUTLINE AROUND THE "MAZE" ARENA 
    start_segment = vec4(-1000,0,-1000,0);
    end_segment = vec4(-1000,0,1000,0);
    wall_points.push_back({start_segment, end_segment});
    
    start_segment = end_segment;
    end_segment = vec4(1000,0,1000,0);
    wall_points.push_back({start_segment, end_segment});

    start_segment = end_segment;
    end_segment = vec4(1000,0, 700,0);
    wall_points.push_back({start_segment, end_segment});

    // HERE IS THE EXIT!!! YAY
    start_segment = end_segment + vec4(0,0,-100,0);
    end_segment = vec4(1000,0,-1000,0);
    wall_points.push_back({start_segment, end_segment});

    start_segment = end_segment;
    end_segment = vec4(-1000,0,-1000,0);
    wall_points.push_back({start_segment, end_segment});
    // END OUTLINE


    start_segment = vec4(1000,0,-10,0);
    end_segment = vec4(1000,0,-1000,0);
    wall_points.push_back({start_segment, end_segment});

    start_segment = end_segment;
    end_segment = vec4(1000, 0,-1000,0);
    wall_points.push_back({start_segment, end_segment});

    start_segment = end_segment;
    end_segment = vec4(500, 0,-500,0);
    wall_points.push_back({start_segment, end_segment});

    start_segment = end_segment;
    end_segment = vec4(400, 0,-500,0);
    wall_points.push_back({start_segment, end_segment});

    //branch:
    vec4 node1 = start_segment;
        start_segment = node1;
        end_segment = vec4(node1.x, 0, -400, 0);
        wall_points.push_back({start_segment, end_segment});

        start_segment = node1;
        end_segment = vec4(node1.x, 0, -600, 0);
        wall_points.push_back({start_segment, end_segment});

    node1 += vec4(-300, 0, 0,0);
        start_segment = node1;
        end_segment = vec4(node1.x, 0, -400, 0);
        wall_points.push_back({start_segment, end_segment});

        start_segment = node1;
        end_segment = vec4(node1.x, 0, -600, 0);
        wall_points.push_back({start_segment, end_segment});

        start_segment = node1;
        end_segment = node1 + vec4(100, 0, 0, 0);
        wall_points.push_back({start_segment, end_segment});

    /* .... */
        /* HYBRID BETWEEN TRAILING AND POINT TO POINT  */
    start_segment = node1;
    end_segment = node1 + vec4(-400, 0, 0, 0);
    wall_points.push_back({start_segment, end_segment});
    node1 = end_segment;

    start_segment = node1;
    end_segment = node1 + vec4(-400, 0, 400, 0);  // adjust this for offset between wall segments..
    wall_points.push_back({start_segment, end_segment});
    node1 = end_segment;

    // STRANGE PARTD THAT SEPERATES THE TWO BIG SUB-ROOMS
    start_segment = node1;
    end_segment = node1 + vec4(-200, 0, 10, 0);  
    wall_points.push_back({start_segment, end_segment});
    node1 = end_segment;

    start_segment = node1;
    end_segment = node1 + vec4(0, 0, 600, 0);  
    wall_points.push_back({start_segment, end_segment});
    node1 = end_segment;

    float hallway_width = 100;
    float hallway_length = 400;
    start_segment = node1 + vec4(hallway_width, 0, 0, 0);          // offset with hybrid
    end_segment = node1 + vec4(hallway_width, 0, -hallway_length, 0);  
    wall_points.push_back({start_segment, end_segment});

 ///////////

    start_segment = node1 + vec4(-200, 0, 100, 0);          // offset with hybrid
    end_segment = node1 + vec4(200, 0, 100, 0);  
    wall_points.push_back({start_segment, end_segment});


    start_segment = node1 + vec4(200, 0, 100, 0);          // offset with hybrid
    end_segment = node1 + vec4(200, 0, -500, 0);  
    wall_points.push_back({start_segment, end_segment});

    node1 = end_segment + vec4(100, 0,-60,0); //  i only want to change nodes when i am done with a branch..


    start_segment = node1 + vec4(0, 0, 0, 0);          // offset with hybrid
    end_segment = node1 + vec4(0, 0, 950, 0);  
    wall_points.push_back({start_segment, end_segment});

    node1 = end_segment;

    start_segment = node1 + vec4(0, 0, 0, 0);          // offset with hybrid
    end_segment = vec4(1000,0, 600,0); // this happens to be the left hand side of the exit..  
    wall_points.push_back({start_segment, end_segment});

    node1 = end_segment;

    // DOOR LOL
    start_segment = node1 + vec4(0, 0, 0, 0);          // offset with hybrid
    end_segment = node1 + vec4(-100,0, 100,0); // this happens to be the left hand side of the exit..  
    wall_points.push_back({start_segment, end_segment});

    // ANGLE TEST: (WORKS!)
    start_segment = node1 + vec4(0, 0, 0, 0);          // offset with hybrid
    end_segment = node1 + vec4(-300,0, -300,0); // this happens to be the left hand side of the exit..  
    wall_points.push_back({start_segment, end_segment});


    vec4 prev_direction = Angel::normalize(end_segment - start_segment);
    node1 = end_segment;
        start_segment = node1;
        end_segment = node1 +  prev_direction*50;
        wall_points.push_back({start_segment, end_segment});

        start_segment = node1;
        end_segment = node1 + Angel::normalize(Angel::cross(prev_direction, vec4(0,1,0)))*100;
        wall_points.push_back({start_segment, end_segment});


    /* NOW: I have a map of all of the points for the walls.. */

    // std::vector<bool> aar; 
    // aar.resize(2000,false);
    // collision_array.resize(2000,aar);

    // int num_wall_points = wall_points.size();
    // for (int i = 0; i < num_wall_points; ++i) {
    //     int _x1 = wall_points[i].p1.x;
    //     int _z1 = wall_points[i].p1.y;

    //     int _x2 = wall_points[i].p2.x;
    //     int _z2 = wall_points[i].p2.y;

    //     collision_array[_x1][_z1] = true; 
    //     collision_array[_x2][_z2] = true; 
    // }


    NUM_ROOMS = 1;

    /* initialize the rooms */
    for (int i = 0; i < NUM_ROOMS; ++i){
        rooms.push_back( new Room(  program_id,
                                    wall_points,
                                    vec4(x_position, y_position, z_position, 0), //offset
                                    width/NUM_ROOMS, 
                                    length/NUM_ROOMS));
    }


    // if (player)
    // {
    //     player->setRoomIndex(0);
    // }


}
Maze::~Maze(){
    for (int i = 0; i < rooms.size(); ++i){
        delete rooms[i];
    }
}

/* called in a timer func..:
    TODO: check collisions */
bool Maze::tick(){
    // for all nearbby linesegments:
    // 


    if (rooms.size() == 0){
        return false;
    }

    // Room* this_room = rooms[player->getRoomIndex()];

    // // TODO:
    // // for every wall in that room, get all wall_points (wall_segments)
    // // and perform the following.. changing the wall_width when needed)    


    // line segment points, where to get these?
    // TRIVIAL SOLUTION: 0(n^2) as n is the number of line segments .....
    // not too bad for now.. otherwise i should partition the points into locality maps 

    float least_min_distance = 1231241;

    int num_wall_points = wall_points.size();
    for (int i = 0; i < num_wall_points; ++i) {
        vec4 s1 = wall_points[i].p1;
        vec4 s2 = wall_points[i].p2;

        vec4 v1 = s2-s1;        // line vector
        vec4 p0 = player->eye;  // player position vector
        
        //float min_distance = 100;
        float length_squared = v1.x*v1.x + v1.y*v1.y + v1.z*v1.z;
        float t = Angel::dot(v1, (p0 - s1)) / length_squared;
        float min_distance = 0;
        if (t < 0.0) {
            min_distance = Angel::length(s1 - p0);
        } else if (t > 1.0) {
            min_distance = Angel::length(s2 - p0);
        } else {
            min_distance = Angel::length(Angel::cross(p0 - s1, p0 - s2))/Angel::length(s2 - s1); 
        }


        float wall_width = 10;
        if (min_distance < least_min_distance){
            least_min_distance = min_distance;
        }
        
        // collide?
        if (min_distance <= (wall_width + player->radius)){
            vec4 dir = Angel::normalize(player->at - player->eye); //player->getDirection();
            vec4 new_dir = ((dir*v1)/Angel::length(v1)) * Angel::normalize(v1);
            vec4 orthoganal_dir = (dir - new_dir);

            // calculate the direction relative to the wall..
            // is it away or towards..
            float predicted_distance;
                p0 = (player->eye + dir*2);
                predicted_distance = Angel::length(Angel::cross(p0 - s1, p0 - s2))/Angel::length(s2 - s1);  

            if (predicted_distance < min_distance ){
                 orthoganal_dir *= -1; // if the palyer is FACING the wall
            } 
             // else the player is NOT facing the wall.

            // //player->setDirection(new_dir);

            // sort of sliding effect
            player->at += new_dir;
            player->eye += new_dir;

            // sort of collision effect..
            // the number 8 seems OK at alleviating any 
            // weird effects
            // TODO: implement some sort of lock
            //  that intercepts the user's controlDirection Vector in some
            // way that prevents the new position from updating..
            // here i have no access..
            // but maybe i could set an opposite force vector on collision:
            // then when the player update's it's position it makes sure to add a
            // any forces applied to it..  
            player->at += 8*orthoganal_dir;
            player->eye += 8*orthoganal_dir;

            p0 = player->eye;
            // player->translate(); // just move away.. this assumes that thedirection is in player coordinales.. not true.
            cout << "COLLISION! " << " @ DISTANCE: " << min_distance << endl;
            //cout << "Player Relocated To: " << Angel::length(Angel::cross(p0 - s1, p0 - s2))/Angel::length(s2 - s1) << endl << endl;
        }

    }

    return true;
}



/* called in display callback:
   TODO: display the room's geometry */
bool Maze::display(){
    for (int i = 0; i < NUM_ROOMS; ++i){
        rooms[i]->display();
    }
    return true;
}


void Maze::attach_player_geometry(Geometry* player){
    this->player = player;
}


