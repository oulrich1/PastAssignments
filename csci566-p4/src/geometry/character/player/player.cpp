#include "player.h"


Player::Player(){
    max_throttle    = THROTTLE_MAX;
    cur_throttle    = 0;
    min_throttle    = 0;

    thetas          = vec4(0,0,0,0);
    direction       = vec4(0,0,0,0);

    current_control_state = 0; // the state mask that is used to control the orientation of the camera..

    player_frozen    = false;

    drag_factor     = 0.95934123; // random
    ROTATE_FACTOR   = 0.81f;

    float player_y = 20;

    eye = vec4( 10, player_y, -100.0, 1.0 );
    at = vec4( 11, player_y, -100.0, 1.0 );
    up = vec4( 0.0, 1.0, 0.0, 0.0 );

radius = 15;

    init_data();
    init_gl();

}
Player::~Player(){

}


void Player::init_data(){
    init_models();
    init_views();
}  
void Player::init_models(){

}
void Player::init_views(){

}
void Player::init_gl(){
    glGenVertexArrays( 1, &(this->vao) );   
    glBindVertexArray( this->vao );         // bind the vertex array object

    glGenBuffers( 1, &(this->vbo) );        
    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );// bind the array buffer object

printf("1.b.1.) Initialized: GPU VAO && VBO specifically for Player\n");

        //     GLuint vPosition = glGetAttribLocation( program_id, "vPosition" );
        // glEnableVertexAttribArray( vPosition );
        // glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
        //            BUFFER_OFFSET(0) );

        // GLuint vColor = glGetAttribLocation( program_id, "vColor" ); 
        // glEnableVertexAttribArray( vColor );
        // glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
        //            BUFFER_OFFSET(sizeof(points)) );

printf("1.b.2.) Initialized: GPU with Player Geometry Data\n");

    // model_view = glGetUniformLocation( program_id, "model_view" );
    // new_color = glGetUniformLocation( program_id, "new_color" );

    // /* belay the possiblity of misuse */
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

}        
void Player::display(){
    /* if any when the has a model..
        render it here.. */
}   

void Player::set_at(vec4 _at){
    at = _at;
    update_view();
}
void Player::set_up(vec4 _up){
    up = _up;
    at.y = eye.y;
    update_view();
}


void Player::update_view(){
    // assert that orientation of position has been updated 
    // with  eye, at, and up vectors..
    // DELEGATE THE CAMERA DO THE ACTUAL PROJECTION STUFF..
    // HERE WE CAN MANIPULATE THE MODEL FOR THE PLAYER
}

/* simulates the flying.. */
bool Player::tick(){

    /* if we need to orient the camera.. control the orientation */
    if(current_control_state & YAW_LEFT) {
        controlStick(vec4(0,-ROTATE_FACTOR,0,0));
    }
    if(current_control_state & YAW_RIGHT) {
        controlStick(vec4(0,ROTATE_FACTOR,0,0));
    }
    if(current_control_state & ROLL_LEFT) {
        controlStick(vec4(0,0,-ROTATE_FACTOR, 0));
    }
    if(current_control_state & ROLL_RIGHT) {
        controlStick(vec4(0,0,ROTATE_FACTOR, 0));
    }
    if(current_control_state & PITCH_DOWN) {
        controlStick(vec4(-ROTATE_FACTOR,0,0, 0));
    }
    if(current_control_state & PITCH_UP) {
        controlStick(vec4(ROTATE_FACTOR,0,0, 0));
    }

    /* if we need to move the camera.. control the direction */
    if(current_control_state & STRAFE_LEFT) {
        controlDirection(vec4(-STRAFE_LEFT_SPEED * sprint_multiplier,0,0, 0));
    }
    if(current_control_state & STRAFE_RIGHT) {
        controlDirection(vec4(STRAFE_RIGHT_SPEED * sprint_multiplier,0,0, 0));
    }
    if(current_control_state & STRAFE_UP) {
        controlDirection(vec4(0,0,STRAFE_UP_SPEED, 0));
    }
    if(current_control_state & STRAFE_DOWN) {
        controlDirection(vec4(0,0,-STRAFE_DOWN_SPEED, 0));
    }
    if(current_control_state & MOVE_FORWARD) {
        controlDirection(vec4(0,0,-MOVE_FORWARD_SPEED * sprint_multiplier, 0));
    }
    if(current_control_state & MOVE_BACKWARD) {
        controlDirection(vec4(0,0,MOVE_BACKWARD_SPEED * sprint_multiplier, 0));
    }


    // non each frame this function is called: 
    // the direction and thetas are being collected..
    // now we need to take action and update the properties 
    // of this geometry's orientation and position so
    // the camera can update it's position based on this 
    // player's attributes
    
    if (player_frozen == false) {
        //cam->walk(vec4(0,0,-((float)cur_throttle/max_throttle) * MAX_SPEED, 0) + this->direction );
        //cam->adjust(thetas);

        translate(vec4(0,0,0, 0) + this->direction );
        rotate(thetas);
        update_view();
        this->thetas -=  this->thetas * drag_factor; // drag the change in angle..
        this->direction -= this->direction * drag_factor;
        return true;
    }
    return false;
}

bool Player::resetOrientation(vec4 up){
    thetas = vec4(0,0,0,0);
    //cam->set_up(up);    
    return true;
}

bool Player::pause(){
    if (player_frozen == false) {
        player_frozen = true;
        return false;
    }
    return true;
}

bool Player::unpause(){
    if (player_frozen == true) {
        player_frozen = false;
        return false;
    }
    return true;
}

/* Throttle Controlls */
string Player::throttleMessage(){
    return "Throttle: " + toString((float)cur_throttle/max_throttle);
}

bool Player::increaseThrottle(){
    if (cur_throttle < max_throttle) {
        cur_throttle += INCR_THROTTLE_FACTOR;
        if (cur_throttle > max_throttle){
            cur_throttle = max_throttle;
        }
        return true;
    } 
    return false;
}

bool Player::decreaseThrottle(){
    if (cur_throttle > min_throttle){
        cur_throttle -= INCR_THROTTLE_FACTOR;
        if (cur_throttle < min_throttle){
            cur_throttle = min_throttle;
        }
        return true;
    }
    return false;
}

float Player::getThrottle(){
    return cur_throttle;
}

bool Player::setThrottle(float throttle){
    if (throttle < min_throttle){
        cur_throttle = min_throttle;
    } else if (throttle > max_throttle){
        cur_throttle = max_throttle;
    } else{
        cur_throttle = throttle;
        return true;
    }
    return false;
}
/* end throttle controls */

// returns the previous multiplier
float Player::setRunSpeedMultiplier(float multiplier){
    float prev_sprint_multiplier = sprint_multiplier;
    sprint_multiplier = multiplier;
    return prev_sprint_multiplier;
} 

void Player::setControlState(int state){
    current_control_state |= state;     // set the state
}

void Player::unsetControlState(int state){
    current_control_state &= (~state);  // clear the state
}


/* STRAFE:  FORWARD(UP & w), BACKWARDS(DOWN & s), 
                LEFT(a), RIGHT(d), 
            UP(x), DOWN(z),         */
bool Player::controlDirection(vec4 dir){

    direction += dir;

    return true;
}

/* ROLL(q | e), PITCH(? ?), YAW(LEFT | RIGHT) */
bool Player::controlStick(vec4 angle_dir){

    thetas += angle_dir;

    return true;
}

bool Player::collided(){
    // if (cam->eye.y < -13){
    //     resetOrientation();
    //     cam->eye.y = -5;
    //     return true;
    // }
    return false;
}


