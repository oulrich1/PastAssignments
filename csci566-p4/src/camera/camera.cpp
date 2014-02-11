#include "camera.h"

Camera::Camera(GLuint program_id){

    /* camera view matrix..  LOCATION IN SHADER */
    view_loc = glGetUniformLocation( program_id, "camera_view");
    
    /* camera projection matrix.. LOCATION IN SHADER */
    projection_loc = glGetUniformLocation( program_id, "projection" );    
    /* - - - - - - - - - - - - - - - - - - - - */

    /* initialized as geometry attributes */
    // if wanting to change inital view. change the player eye and at..
    // eye = vec4( 0, 2, 2, 1.0 );
    // at = vec4( 0.0, 1.0, -1.0, 1.0 );
    // up = vec4( 0.0, 1.0, 0.0, 0.0 );

    update_view(); 
    update_proj();

    world_geometry = NULL;

cout << "CAM VIEW: " << view_mat4 << endl;
cout << "CAM PROJ: " << projection_mat4 << endl;

}

Camera::~Camera(){
    
}

void Camera::tick(){
    update_view(world_geometry->eye, world_geometry->at, world_geometry->up);
}

Geometry* Camera::attach(Geometry* _world_geometry){
    Geometry* prev_wg = world_geometry;
    world_geometry = _world_geometry;
    return prev_wg;
}

void Camera::set_at(vec4 _at){
    at = _at;
    update_view();
}
void Camera::set_up(vec4 _up){
    up = _up;
    at.y = eye.y;
    update_view();
}

void Camera::update_proj(){
    projection_mat4 = Perspective( fovy, aspect, zNear, zFar ); 
    glUniformMatrix4fv( projection_loc, 1, GL_TRUE, projection_mat4);
}

void Camera::update_view(vec4 _eye, vec4 _at, vec4 _up){
    view_mat4 = LookAt( _eye, _at, _up );
    glUniformMatrix4fv( view_loc, 1, GL_TRUE, view_mat4 );
}

void Camera::update_view(){
    view_mat4 = LookAt( eye, at, up );
    glUniformMatrix4fv( view_loc, 1, GL_TRUE, view_mat4 );
}

void Camera::constrict_angles(){
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

void Camera::adjust(vec4 direction){
    if(length(direction) == 0)
        return;
    
    
    theta_x = dTheta * direction.x;
    theta_y = dTheta * -direction.y;
    theta_z = dTheta * -direction.z;

    vec4 thetas = vec4(theta_x, theta_y, theta_z, 0); 

    constrict_angles(); 
    vec4 look = eye - at;
         look = vec4(look.x, look.y, look.z, 0);

    vec4 side = -cross( normalize(look), up);

    mat4 M = mat4(normalize(side), normalize(up), normalize(look), vec4(0,0,0,0) ); //x y z w
    /* M is the basis matrix for the camera...
        vector in Standard Basis Space S can 
        be transformed into vector in M basis B'
       or vector can be transformed from B' to S:
        M^-1 == transpose(M)   */
    mat4 CameraToStandardBasis_M = transpose(M);

    vec4 thetas_prime = CameraToStandardBasis_M * thetas;
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

    update_view();

}

/* Walk and Turn ::updates the view:: */
void Camera::walk(vec4 direction){
    if(length(direction) == 0)
        return;

    mat4 M = mat4(normalize(vec4(-cross(normalize(eye - at), up), 0)), normalize(up), normalize(eye - at), vec4(0,0,0,0) );
    mat4 CameraToStandardBasis_M = transpose(M);

    direction = CameraToStandardBasis_M * direction;
    //direction = normalize(direction);
    direction = direction*dy;

    eye += direction;
    at += direction;
    
    update_view();
}

void Camera::offsetOrientation(vec2 direction){

    update_view();
}
