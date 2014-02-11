
#include "geometry.h"


Geometry::Geometry(){
    I = identity(); //matrix

    eye = vec4( 0, 2, 2, 1.0 );
    at = vec4( 0.0, 2.0, -1.0, 1.0 );
    up = vec4( 0.0, 1.0, 0.0, 0.0 );

    drag_factor = 0.0001; // default

    radius = 40; //default
    room_index = 0; // always the first room
}
Geometry::Geometry(GLuint _program_id){
    program_id = _program_id;
}

Geometry::~Geometry(){
    
}


void Geometry::constrict_angles(){
    if (theta_y >= 360 || theta_y <= -360) {
        theta_y = 0;
    }
    if (theta_x >= 360 || theta_x <= -360) {
        theta_x = 0;
    }
    if (theta_z >= 360 || theta_z <= -360) {
        theta_z = 0;
    }
}



/* THIS SHOULD PROBABLY BE COMMON GEOMETRY CODE FOR ROTATE AND TRANSLATE */

/* The following two functions update the  */
/* This function will update the model view matrix 
    and send it to the GPU.. now geometry object
    will rotate */
void Geometry::rotate(vec4 dir){
    if(length(dir) == 0)
            return;
        
    float theta_x = dTheta *  dir.x;
    float theta_y = dTheta * -dir.y;
    float theta_z = dTheta * -dir.z;

    vec4 dthetas = vec4(theta_x, theta_y, theta_z, 0); 

    constrict_angles(); 
    vec4 look = eye - at;
         look = vec4(look.x, look.y, look.z, 0);

    vec4 side = -cross( normalize(look), up);

    mat4 M = mat4(  normalize(side), 
                    normalize(up), 
                    normalize(look), 
                    vec4(0,0,0,0) ); //x y z w

    /* M is the basis matrix for the camera...
        M^-1 == transpose(M)   */
    mat4 CameraToStandardBasis_M = transpose(M);

    /* --- calculated by some change in theta/angle --- */

    vec4 thetas_prime = CameraToStandardBasis_M * dthetas;
    // YAW & PITCH (translate because at is not a vector.. its a point)
    at = Translate(eye.x, eye.y, eye.z) *  
        RotateX(thetas_prime.x) * 
        RotateY(thetas_prime.y) * 
        RotateZ(thetas_prime.z) * 
        Translate(-eye.x, -eye.y, -eye.z) * at;

    // PITCH & ROLL (luckily up is a vector..)
    look = eye - at;
    up = RotateX(thetas_prime.x) *
        RotateY(thetas_prime.y) * 
        RotateZ(thetas_prime.z) * up;

    
}


/* This function will update the model view matrix 
    and send it to the GPU.. now geometry object
    will move/translate */
void Geometry::translate(vec4 dir){
    if(length(dir) == 0)
        return;

    vec4 unit_lookat_normal = normalize(eye - at);
    mat4 M = mat4(  normalize(vec4(-cross(unit_lookat_normal, up), 0)), 
                    normalize(up), 
                    unit_lookat_normal, 
                    vec4(0,0,0,0)  );

    mat4 CameraToStandardBasis_M = transpose(M);

    dir = CameraToStandardBasis_M * dir;
    dir = dir*dx;   // dx defined in header (small change in position)

    /* calculated by some dx,dy,dz */
    eye += dir;
    at  += dir;

    
}




/*      - - - - - - - - - - -       */
/*      STATIC FUNCTIONS            */

/*

    // the points that compose a cube
    vec4* mycubeverts = Geometry::createUnitCube();
    
    // given the points, generate a gl cube 
    // which is an array of contiguious vertexes
    vec4** mycubeverts_openglpoints = glcube( mycubeverts );

    drawArrays ( mycubevers_openglpoints );




 */


// quad made from two triangles.. no strips
vec4* Geometry::glquad( vec4 *cur_vertices, int a, int b, int c, int d ) {
    
    int iter = 0;
    vec4* points = new vec4[6];
    points[iter] = cur_vertices[a]; iter++;
    points[iter] = cur_vertices[b]; iter++;
    points[iter] = cur_vertices[c]; iter++;
    points[iter] = cur_vertices[a]; iter++;
    points[iter] = cur_vertices[c]; iter++;
    points[iter] = cur_vertices[d]; 
    return points;
}




vec4* Geometry::glcube( vec4 *verts ) {
    vec4* _cube = new vec4[36]; // 6 faces * 6 points per face
    vec4* _tmpface;
     int iter = 0;

    _tmpface = glquad(verts, 1, 0, 3, 2 );
    for (int i = 0; i < 6; ++i){
        _cube[iter] = _tmpface[i];
        iter++;
    }
    delete _tmpface;

    _tmpface = glquad(verts, 2, 3, 7, 6 );
    for (int i = 0; i < 6; ++i){
        _cube[iter] = _tmpface[i];
        iter++;
    }
    delete _tmpface;

    _tmpface = glquad(verts, 3, 0, 4, 7 );
    for (int i = 0; i < 6; ++i){
        _cube[iter] = _tmpface[i];
        iter++;
    }
    delete _tmpface;

    _tmpface = glquad(verts, 6, 5, 1, 2 );
    for (int i = 0; i < 6; ++i){
        _cube[iter] = _tmpface[i];
        iter++;
    }
    delete _tmpface;

    _tmpface = glquad(verts, 4, 5, 6, 7 );
    for (int i = 0; i < 6; ++i){
        _cube[iter] = _tmpface[i];
        iter++;
    }
    delete _tmpface;

    _tmpface = glquad(verts, 5, 4, 0, 1 );
    for (int i = 0; i < 6; ++i){
        _cube[iter] = _tmpface[i];
        iter++;
    }
    delete _tmpface;
    _tmpface = NULL;

    return _cube;
}





vec4*   Geometry::createUnitTriangle(){
    int i = 0;
    vec4* ret = new vec4[3];
    ret[i] = point4( -U_CUBE_C, -U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    ret[i] = point4(         0,  U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    ret[i] = point4(  U_CUBE_C,  -U_CUBE_C,  U_CUBE_C, 1.0 );
    return ret;
}

vec4*   Geometry::createUnitPlane(){
    int i = 0;
    vec4 * ret = new vec4[4];
    ret[i] = point4( -U_CUBE_C, -U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    ret[i] = point4( -U_CUBE_C,  U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    ret[i] = point4(  U_CUBE_C,  U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    ret[i] = point4(  U_CUBE_C, -U_CUBE_C,  U_CUBE_C, 1.0 );
    return ret;
}

vec4* Geometry::createUnitCube(){
    int i = 0;
    vec4 * vertices = new vec4[8];

    vertices[i] = point4( -U_CUBE_C, -U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    vertices[i] = point4( -U_CUBE_C,  U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    vertices[i] = point4(  U_CUBE_C,  U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    vertices[i] = point4(  U_CUBE_C, -U_CUBE_C,  U_CUBE_C, 1.0 ); i++;
    vertices[i] = point4( -U_CUBE_C, -U_CUBE_C, -U_CUBE_C, 1.0 ); i++;
    vertices[i] = point4( -U_CUBE_C,  U_CUBE_C, -U_CUBE_C, 1.0 ); i++;
    vertices[i] = point4(  U_CUBE_C,  U_CUBE_C, -U_CUBE_C, 1.0 ); i++;
    vertices[i] = point4(  U_CUBE_C, -U_CUBE_C, -U_CUBE_C, 1.0 ); //end
    return vertices;
}

vec4* Geometry::createUnitSphere(){
    int i = 0; i = 1;
    vec4* ret = new vec4[3];
    return ret;
}



vec4* Geometry::createUnitColors(){
    int i = 0;
    vec4 * vertex_colors = new vec4[8];

    vertex_colors[i] = color4( 0.2, 0.21, 0.22, 1.0 ); i++;  // black
    vertex_colors[i] = color4( 0.2, 0.212, 0.23, 1.0 ); i++;
    vertex_colors[i] = color4( 0.2, 0.21, 0.21, 1.0 ); i++;
    vertex_colors[i] = color4( 0.2, 0.22, 0.21, 1.0 ); i++;
    vertex_colors[i] = color4( 0.2, 0.22, 0.22, 1.0 ); i++;
    vertex_colors[i] = color4( 0.2, 0.22, 0.24, 1.0 ); i++;
    vertex_colors[i] = color4( 0.2, 0.22, 0.23, 1.0 ); i++;
    vertex_colors[i] = color4( 0.2, 0.212, 0.22, 1.0 ); 
    // vertex_colors[i] = color4( 1.0, 0.0, 0.0, 1.0 ); i++;  // red
    // vertex_colors[i] = color4( 1.0, 1.0, 0.0, 1.0 ); i++;  // yellow
    // vertex_colors[i] = color4( 0.0, 1.0, 0.0, 1.0 ); i++;  // green
    // vertex_colors[i] = color4( 0.0, 0.0, 1.0, 1.0 ); i++;  // blue
    // vertex_colors[i] = color4( 1.0, 0.0, 1.0, 1.0 ); i++; // magenta
    // vertex_colors[i] = color4( 1.0, 1.0, 1.0, 1.0 ); i++;  // white
    // vertex_colors[i] = color4( 0.0, 1.0, 1.0, 1.0 );   // cyan
    /* colors and points for the unit cube have been initialized */
    return vertex_colors;
}


int     Geometry::getRoomIndex(){return room_index; }
void    Geometry::setRoomIndex(int index){ room_index = index; }