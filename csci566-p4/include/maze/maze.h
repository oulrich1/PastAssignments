#include "room.h"

#ifndef MAZE_H
#define MAZE_H 

/* All that maze is really, is a collection
    of rooms... */
class Maze
{
public:
    Maze(GLuint _program_id);
    ~Maze();

    bool tick();        // calculate interactions and collisions
    bool display();     // displays all rooms in this maze..

   
    /* so the maze can keep track of interactions */
    void attach_player_geometry(Geometry* player);
    void trigger_lighting(){
        if (rooms[0]){
            rooms[0]->trigger_lighting();
        }
    }

protected:
    Geometry*   player;
    GLuint      program_id;

    // point pair is a struct of two vec4's
    // see utils.h
    std::vector<pointpair> wall_points;

private:
    float width;
    float length;
    float height;

    float x_position;
    float y_position;
    float z_position;

    int NUM_ROOMS;

    std::vector<Room*> rooms;

    // THIS WOULD BE TOO CRAZY: 
    // (using wallpoints to calculate segment collision instead..)
    std::vector<std::vector<bool> > collision_array;
};

#endif