/* main.cpp
 * 
 * Entry point for the game.
 *
 */

#include "game.h"

int main(int argc, char* argv[]) {
    Game maze(&argc, argv);
    maze.run();
    return 0;
}
