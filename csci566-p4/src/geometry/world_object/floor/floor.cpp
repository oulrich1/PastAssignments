


#include "floor.h"
Floor::Floor(GLuint _program_id, vec4 _offset) : Geometry(_program_id){
	offset = _offset;

	float dummy_width = 100;
	float dummy_length = 150;

	init_logic(dummy_width, dummy_length); // TODO: decouple this with a package of some sort..
	init_data();
	init_gl();
}

Floor::Floor(GLuint _program_id, vec4 _offset, float width, float length) : Geometry(_program_id){
	offset = _offset;

	init_logic(width, length); // TODO: decouple this with a package of some sort..
	init_data();
	init_gl();
}

Floor::~Floor(){
	delete points;
	delete colors;

	delete model_view_matricies;
    delete models;
    delete views;
}

void Floor::init_logic(float width, float length){


	// FILE * file;
	// //int number_of_bytes_in_brick_texture = 256 * 256 * 3;

	// // texture image is a char* array as a member of the floor object
	// texture_image = (char*)malloc( 256 * 256 * 3 );
	// file = fopen( "assets/images/ground/brick.rgb", "rb" );
	// if(file != NULL){
	// 	cout << "FLOOR: SUCCESSFULLY READ BRICK TEXTURE! " << endl;
	// 	cout << endl << endl;
	// 	int err = fread( texture_image, 1, 256 * 256 * 3, file );
	// 	fclose( file );
	// }
	// free(texture_image);

	light_on = 1;

	
	floor_width = width;
	floor_length = length;

	x_position = offset.x;
	y_position = offset.y;
	z_position = offset.z;


	VERTEX_COUNT = 6;

	VERTEX_BUFFER_OFFSET = sizeof(vec4) * VERTEX_COUNT;
	COLOR_BUFFER_OFFSET = sizeof(vec4) * VERTEX_COUNT;
	TEXTURE_BUFFER_OFFSET = sizeof(vec2) * VERTEX_COUNT;

	TOTAL_BUFFER_OFFSET = VERTEX_BUFFER_OFFSET + COLOR_BUFFER_OFFSET + TEXTURE_BUFFER_OFFSET;

	points = new vec4[VERTEX_COUNT]; // triangle strips
	colors = new vec4[VERTEX_COUNT];

	NUM_COMPONENTS = 1; 	// floor is currently built with one floor

    model_view_matricies = new mat4[NUM_COMPONENTS];
    models = new mat4[NUM_COMPONENTS];
    views = new mat4[NUM_COMPONENTS];
}

void Floor::init_data(){

	int iter = 0;

	points[iter] = vec4( 	x_position, 
							y_position, 
							z_position - floor_length, 1); 
	iter++;

	points[iter] = vec4(	x_position, 
							y_position, 
							z_position, 1); 
	iter++;

	points[iter] = vec4(	x_position + floor_width, 
							y_position, 
							z_position, 1); 
	iter++;

	points[iter] = vec4( 	x_position, 
							y_position, 
							z_position - floor_length, 1); 
	iter++;

	points[iter] = vec4(	x_position + floor_width, 
							y_position, 
							z_position, 1); 
	iter++;

	points[iter] = vec4(	x_position + floor_width, 
							y_position, 
							z_position - floor_length, 1); 
	iter++;


	if (iter != VERTEX_COUNT){
		cerr << "Warning: Floor vertex POSITION count does not match actual" << 
		"count of initialized vertecies. In floor.cpp!" << endl << endl;
	}
	iter = 0;
	colors[iter++] = vec4(	0.0, 
							0.2, 
							0.34, 1); 

	colors[iter++] = vec4(	0.0, 
							0.4, 
							0.34, 1); 

	colors[iter++] = vec4(	0.0, 
							0.1, 
							0.9, 1); 

	colors[iter++] = vec4(	0.15, 
							0.2, 
							0.5, 1); 

	colors[iter++] = vec4(	0.0, 
							0.4, 
							0.9, 1); 

	colors[iter++] = vec4(	0.1, 
							0.3, 
							0.8, 1); 

	if (iter != VERTEX_COUNT){
		cerr << "Warning: Floor vertex COLOR count does not match actual" << 
		"count of initialized vertecies. In floor.cpp!" << endl << endl;
	}

	init_models();
	init_views();

	for (int i = 0; i < NUM_COMPONENTS; ++i) {
        model_view_matricies[i] =  views[i] * models[i];
    }


}   


void Floor::init_models() {

    for (int i = 0; i < NUM_COMPONENTS; ++i) {
	    models[i] = mat4({1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1});  
    }



}


// create the views.. currently not necssary
void Floor::init_views(){
    mat4 view = mat4({1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1});
    for (int i = 0; i < NUM_COMPONENTS; ++i){
        views[i] = view;
    }
}



/* setup some vbo for the points of the floor
	get the position of the model_view matrixis in the shader */
void Floor::init_gl(){

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

// 	int width, height;
// unsigned char* soilimage =
// SOIL_load_image("sample.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	/* Generate texture object and initialize  */
	glGenTextures( 1, &texture_id ); //texture_id in geometry.h
    
    glBindTexture( GL_TEXTURE_2D, texture_id );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, TextureSize, TextureSize, 0,
		  GL_RGB, GL_UNSIGNED_BYTE, /*texture_image*/ cobblestone_ground );
// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
//           GL_UNSIGNED_BYTE, soilimage);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture_id );

// SOIL_free_image_data(soilimage);

	/* SET UP VAO AND VBO with Vertex, Color, Texture Data */

    glGenVertexArrays( 1, &(this->vao) );   
    glBindVertexArray( this->vao );         // bind the vertex array object

    glGenBuffers( 1, &(this->vbo) );        
    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );// bind the array buffer object

    GLintptr VERTEX_COLOR_BUFFER_OFFSETS = VERTEX_BUFFER_OFFSET + COLOR_BUFFER_OFFSET;

   	/*
	   	VERTEX_BUFFER_OFFSET
		COLOR_BUFFER_OFFSET
		TEXTURE_BUFFER_OFFSET
	*/

    glBufferData( GL_ARRAY_BUFFER, TOTAL_BUFFER_OFFSET, NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, VERTEX_BUFFER_OFFSET, points );
        glBufferSubData( GL_ARRAY_BUFFER, VERTEX_BUFFER_OFFSET, COLOR_BUFFER_OFFSET, colors );

            // texture coordinates
    	glBufferSubData( GL_ARRAY_BUFFER, VERTEX_COLOR_BUFFER_OFFSETS, 
    						TEXTURE_BUFFER_OFFSET, tex_coords );


printf("1.b.1.) Initialized: GPU VAO && VBO specifically for Floor: VERTEX, COLOR, TEXTURES\n");

        GLuint vPosition = glGetAttribLocation( program_id, "vPosition" );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                   BUFFER_OFFSET(0) );

        GLuint vColor = glGetAttribLocation( program_id, "vColor" ); 
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                   BUFFER_OFFSET(VERTEX_BUFFER_OFFSET) );
       
        GLuint vTexCoord = glGetAttribLocation( program_id, "vTexCoord" );
	    glEnableVertexAttribArray( vTexCoord );
	    glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
				   BUFFER_OFFSET(VERTEX_COLOR_BUFFER_OFFSETS) );

	    GLuint vNormal = glGetAttribLocation( program_id, "vNormal" );
		   glEnableVertexAttribArray( vNormal );
		   glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE,0,
		      BUFFER_OFFSET(VERTEX_COLOR_BUFFER_OFFSETS + sizeof(cobblestone_ground)));


		      // initialize lighting parameters
   vec4 light_ambient( 1.0, 1.0, 1.0, 1.0 );
   vec4 light_diffuse( 1.0, 1.0, 1.0, 1.0 );
   vec4 light_specular( 1.0, 1.0, 1.0, 1.0 );
   vec4 material_ambient( 0.2, 0.2, 0.2, 1.0 );
   vec4 material_diffuse( 0.8, 0.0, 0.0, 1.0 );
   vec4 material_specular( 0.0, 0.0, 0.5, 1.0 );
   float  material_shininess = 50.0;
   vec4 ambient_product = light_ambient * material_ambient;
   vec4 diffuse_product = light_diffuse * material_diffuse;
   vec4 specular_product = light_specular * material_specular;


      // send lighting parameters to the shader
   glUniform4fv(
      glGetUniformLocation(program_id, "AmbientProduct"), 1, ambient_product);
   glUniform4fv(
      glGetUniformLocation(program_id, "DiffuseProduct"), 1, diffuse_product);
   glUniform4fv(
      glGetUniformLocation(program_id, "SpecularProduct"), 1, specular_product);
   glUniform1f(
      glGetUniformLocation(program_id, "Shininess"), material_shininess);


printf("1.b.2.) Initialized: Floor: enabled attributes: Position, Color, TextCoord, and possibly lighting\n");

    /* find location of the mv and proj matrix vars in vshader */
    model_view = glGetUniformLocation( program_id, "model_view" );
    new_color = glGetUniformLocation( program_id, "new_color" );
    texture_pos =  glGetUniformLocation( program_id, "texture");



	normalMatrixLoc = glGetUniformLocation(program_id, "normalMatrix" );
	lightLoc = glGetUniformLocation(program_id, "aLight");
	addAmbientLoc = glGetUniformLocation(program_id, "addAmbient");
	addDiffuseLoc = glGetUniformLocation(program_id, "addDiffuse");
	addSpecularLoc = glGetUniformLocation(program_id, "addSpecular");


    free(texture_image);


printf("1.b.3.) found the locations of uniform variable 'model_view': %u\n", model_view);
    /* belay the possiblity of misuse */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}        

void Floor::display(){
    glUseProgram( program_id );
    glBindVertexArray( this->vao );         	 // bind the vertex array object
    glBindBuffer( GL_ARRAY_BUFFER, this->vbo );  // now bind the vbo tha tcontain the data inside

    	// draw the floor..
    	glActiveTexture(GL_TEXTURE0);
     	glBindTexture( GL_TEXTURE_2D, texture_id );
        glUniform1i(texture_pos, 0 );
        
        glUniformMatrix4fv( model_view, 1, GL_TRUE, model_view_matricies[0] );
        glUniform1i(glGetUniformLocation( program_id, "USE_COLOR_BUFFER" ), 1);


              // set the light position or direction and send to shader
      // the light can be rotated about the X axis
      vec4 light = vec4(0.0, 0.0, 0.0, 0);
      light.y = radius*sin(DegreesToRadians*1);
      light.z = radius*cos(DegreesToRadians*1);
      glUniform4fv(lightLoc,1, light);

      // calculate the normal matrix and send to the shader
      mat3 normalMatrix = InverseTranspose(model_view);
      glUniformMatrix3fv(normalMatrixLoc, 1, GL_TRUE, normalMatrix);

        // glUniform4fv(new_color, 1, color4( 1.0, 0.0, 0.0, 1.0 ));
    glDrawArrays( GL_TRIANGLES, 0, VERTEX_COUNT );
    // glBindTexture( GL_TEXTURE_2D, 0 ); // just in case..
}    
