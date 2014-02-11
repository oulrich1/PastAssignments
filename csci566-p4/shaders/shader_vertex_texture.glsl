#version 150 

in  vec4 vPosition;
in  vec4 vColor;

out vec4 color;

in  vec2 vTexCoord;
out vec2 texCoord;


uniform mat4 model_view;
uniform mat4 camera_view;
uniform mat4 projection;

uniform vec4 new_color;

uniform int USE_COLOR_BUFFER;

void main() 
{

    	// model_view matrix {object.view * object.model}
        // camera_view controls the entire world view and 
        // is only changed by the camera.. 
        //      (thetas change in application program)
    gl_Position =  projection * camera_view * model_view * vPosition;

        // new_color is used for solid colors
        // vColor is used for setting color 
        //  from array of colors
    if(USE_COLOR_BUFFER == 1){
        color = vColor; //vColor
    } else {
        color = new_color;
    }

    texCoord    = vTexCoord;

} 