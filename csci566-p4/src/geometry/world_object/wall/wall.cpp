#include "wall.h"


WallProperties Wall::wall_properties = WallProperties();

Wall::Wall(GLuint _program_id, vec4 _room_origin, float width, float height) : Geometry(_program_id){
    room_origin = _room_origin;
    init_logic(width, height); // TODO: decouple this with a package of some sort..
    init_data();
    init_gl();


}
Wall::~Wall(){

}

void Wall::init_logic(float width, float height){

    // these are dependant on the 
    // instance transformation
    start.x = 0;
    start.y = 0;
    start.z = 0;
    
    end.x = 0;
    end.y = 0;
    end.z = 0;


    start.height = height;
    end.height = height;


    // direction =  vec4(end.x,end.y,end.z, 0) - vec4(start.x,start.y,start.z, 0);
    average_width = width;
    average_height = (start.height + end.height) / 2;


    /* geometry init */
    VERTEX_COUNT = 36; // quad triangle strip

    
    VERTEX_BUFFER_OFFSET = sizeof(Wall::wall_properties.glcubevertices);
    COLOR_BUFFER_OFFSET = sizeof(Wall::wall_properties.glcubecolors);
    TEXTURE_BUFFER_OFFSET = 0;

    TOTAL_BUFFER_OFFSET = VERTEX_BUFFER_OFFSET + COLOR_BUFFER_OFFSET + TEXTURE_BUFFER_OFFSET;

    points = new vec4[VERTEX_COUNT]; // triangle strips
    colors = new vec4[VERTEX_COUNT];

    NUM_COMPONENTS = 1;     // floor is currently built with one floor

    model_view_matricies = new mat4[NUM_COMPONENTS];
    models = new mat4[NUM_COMPONENTS];
    views = new mat4[NUM_COMPONENTS];
}

void Wall::init_data(){



    // int iter = 0;
    // points[iter] = vec4(    start.x, 
    //                         start.y + start.height, 
    //                         start.z, 1); 
    // iter++;

    // points[iter] = vec4(    start.x, 
    //                         start.y, 
    //                         start.z, 1); 
    // iter++;

    // points[iter] = vec4(    end.x, 
    //                         end.y + end.height, 
    //                         end.z, 1); 
    // iter++;

    // points[iter] = vec4(    end.x, 
    //                         end.y, 
    //                         end.z, 1); 
    // iter++;




    // if (iter != VERTEX_COUNT){
    //     cerr << "Warning: Floor vertex POSITION count does not match actual" << 
    //     "count of initialized vertecies. In floor.cpp!" << endl << endl;
    // }
    // iter = 0;
    // colors[iter++] = vec4(  0.7, 
    //                         0.2, 
    //                         0.3, 1); 

    // colors[iter++] = vec4(  0.7, 
    //                         0.3, 
    //                         0.5, 1); 

    // colors[iter++] = vec4(  0.7, 
    //                         0.2, 
    //                         0.5, 1); 

    // colors[iter++] = vec4(  0.7, 
    //                         0.2, 
    //                         0.4, 1); 


    // if (iter != VERTEX_COUNT){
    //     cerr << "Warning: Floor vertex COLOR count does not match actual" << 
    //     "count of initialized vertecies. In floor.cpp!" << endl << endl;
    // }

    init_models();
    init_views();

    for (int i = 0; i < NUM_COMPONENTS; ++i) {
        model_view_matricies[i] =  views[i] * models[i];
    }
}



void Wall::init_models() {

    for (int i = 0; i < NUM_COMPONENTS; ++i) {
        models[i] =  mat4({1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1});  
    }



}


// create the views.. currently not necssary
void Wall::init_views(){
    mat4 view = mat4({1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1});
    for (int i = 0; i < NUM_COMPONENTS; ++i){
        views[i] = view;
    }
}

void Wall::init_gl(){

     // program_id = InitShader( SHADER_PATH("shader_vertex_texture.glsl"), 
  //                            SHADER_PATH("shader_fragment_texture.glsl") );
  //   glUseProgram( program_id );

    // http://www.imagemagick.org/Magick++/Image.html
    /* Retrieve the texture for the floor */
    //cobblestone_ground = rgb data for each pixel..
     
    GLubyte d = 255;
   for ( int i = 0; i < TextureSize; i++ ) {
        for ( int j = 0; j < TextureSize; j++ ) {
            //GLubyte c = (((i & 0x40) == 0) ^ ((j & 0x40)  == 0)) * 255;
            cobblestone_ground[i][j][0]  = d;
            cobblestone_ground[i][j][1]  = d;
            cobblestone_ground[i][j][2]  = 200-d;
            d--;
        }
        d = 255;
    }

//  int width, height;
// unsigned char* soilimage =
// SOIL_load_image("sample.jpg", &width, &height, 0, SOIL_LOAD_RGB);

    /* Generate texture object and initialize  */
    glGenTextures( 1, textures );
    
    glBindTexture( GL_TEXTURE_2D, textures[0] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, TextureSize, TextureSize, 0,
          GL_RGB, GL_UNSIGNED_BYTE, cobblestone_ground );
// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
//           GL_UNSIGNED_BYTE, soilimage);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, textures[0] );

// SOIL_free_image_data(soilimage);

    /* SET UP VAO AND VBO with Vertex, Color, Texture Data */

    glGenVertexArrays( 1, &(this->vao) );   
    glBindVertexArray( this->vao );         // bind the vertex array object

    glGenBuffers( 1, &(this->vbo) );        
    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );// bind the array buffer object

    GLintptr VERTEX_COLOR_BUFFER_OFFSETS = VERTEX_BUFFER_OFFSET + COLOR_BUFFER_OFFSET;
    (void)VERTEX_COLOR_BUFFER_OFFSETS;
    /*
        VERTEX_BUFFER_OFFSET
        COLOR_BUFFER_OFFSET
        TEXTURE_BUFFER_OFFSET
    */

    glBufferData( GL_ARRAY_BUFFER, TOTAL_BUFFER_OFFSET, NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, VERTEX_BUFFER_OFFSET, Wall::wall_properties.glcubevertices );
        glBufferSubData( GL_ARRAY_BUFFER, VERTEX_BUFFER_OFFSET, COLOR_BUFFER_OFFSET, Wall::wall_properties.glcubecolors );

        //     // texture coordinates
        // glBufferSubData( GL_ARRAY_BUFFER, VERTEX_COLOR_BUFFER_OFFSETS, 
        //                     TEXTURE_BUFFER_OFFSET, tex_coords );


printf("1.b.1.) Initialized: GPU VAO && VBO specifically for Floor: VERTEX, COLOR, TEXTURES\n");

        GLuint vPosition = glGetAttribLocation( program_id, "vPosition" );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                   BUFFER_OFFSET(0) );

        GLuint vColor = glGetAttribLocation( program_id, "vColor" ); 
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                   BUFFER_OFFSET(VERTEX_BUFFER_OFFSET) );
       
        // GLuint vTexCoord = glGetAttribLocation( program_id, "vTexCoord" );
        // glEnableVertexAttribArray( vTexCoord );
        // glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
        //            BUFFER_OFFSET(VERTEX_COLOR_BUFFER_OFFSETS) );


printf("1.b.2.) Initialized: Floor: enabled attributes: Position, Color, TextCoord\n");

    /* find location of the mv and proj matrix vars in vshader */
    model_view = glGetUniformLocation( program_id, "model_view" );
    new_color = glGetUniformLocation( program_id, "new_color" );
    // texture_pos =  glGetUniformLocation( program_id, "texture");

    

printf("1.b.3.) found the locations of uniform variable 'model_view': %u\n", model_view);
    /* belay the possiblity of misuse */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// the translate (trans) is always relative to the room_origin
void Wall::pushInstance(vec3 trans, vec3 scale, vec3 rot){
    wall_instance_matrices.push_back(   Translate(trans /*+ vec3(room_origin.x, room_origin.y, room_origin.z)*/) * 
                                        RotateZ(rot.z) * 
                                        RotateY(rot.y) * 
                                        RotateX(rot.x) *
                                        Scale(scale)  );
}
                       
void Wall::display(){
    glUseProgram( program_id );
    glBindVertexArray( this->vao );              // bind the vertex array object
    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );  // now bind the vbo tha tcontain the data inside

    int num_wall_instances = wall_instance_matrices.size();
    for (int i = 0; i < num_wall_instances; ++i){
        // draw a wall texture 
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture( GL_TEXTURE_2D, textures[0] );
        // glUniform1i(texture_pos, 0 );
        
        glUniformMatrix4fv( model_view, 1, GL_TRUE, wall_instance_matrices[i] * model_view_matricies[0] );
        glUniform1i(glGetUniformLocation( program_id, "USE_COLOR_BUFFER" ), 1);
        // glUniform4fv(new_color, 1, color4( 1.0, 0.0, 0.0, 1.0 ));
        glDrawArrays( GL_TRIANGLES, 0, VERTEX_COUNT );
        // glBindTexture( GL_TEXTURE_2D, 0 ); // just in case..
    }

}

point Wall::getStart(){
    return start;
}
point Wall::getEnd(){
    return end;
}