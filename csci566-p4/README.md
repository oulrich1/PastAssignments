
csci566 Project 4: Maze
==========================================

Phase ??: Lighting

TODO:
------------------------------------------
    LIGHTING
    TEXTURES // 



To Compile and Run:
------------------------------------------

    To Run: 
        ./bin/maze  or  ./run

    NOTE: If you dont have premake4 installed, its safer to just use the options above

    Trying anything below could remove the makefiles that had been generated..


    There are two ways to build this:
        - using the scripts "install" and "run"
            --  install: makes sure everything is cleaned and rebuilds everythin!
            --  run:     cleans the objects and rebuilds (if specified, user can rebuild the makefiles with -c)

            ./install
            ./run       # will run make if some code changed.. otherwise it just runs maze..

            or

            ./run -c

        - using premake4 and make:



    To Clean only object files: 
        ./run -cc




Dependancies:
------------------------------------------
    
    premake4    (if you want to rebuild the make files)
                (otherwise its not necessary if you jsut need to recompile it.. 
                    makefiels have already been generated..)

    g++-4.7 -std=c++0x  
    
    -lglut -lGLEW -lGL -lGLU -lm 
    (as usual)


Controls:
------------------------------------------
    Plane Controls:

    r:  reset
    q:  quit

    A:  Strafe Left
    D:  Strafe Right

    SHIFT+ : Sprint

    LEFT_ARROW  :   Turn Left (CCW)
    RIGHT_ARROW :   Turn Right (CW)
    UP_ARROW    :   Move Forwards
    DOWN_ARROW  :   Move Backwards




Challenges:
------------------------------------------
    Definitely the largest project. I had a hard time loading textures
    Tried using the ImageMagick Library to load images. however, thre was an 
    issue with Magick++.h. I tried using 'convert' i was able to create a 
    rgb file and load it. However, i must be coding the textures incorrectly
    .. it seg faults sometimes

    Working on lighting at the moment


Brick Texture From:

http://www.sxc.hu/assets/8/73196/brick-texture-1-992018-m.jpg

=============
MAZE
=============
