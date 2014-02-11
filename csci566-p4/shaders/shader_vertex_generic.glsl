#version 150 

in  vec4 vPosition;
in  vec4 vColor;
in  vec2 vTexCoord;
in  vec3 vNormal;

out vec4 color;
out vec2 texCoord;


uniform mat4 model_view;
uniform mat4 camera_view;
uniform mat4 projection;
uniform vec4 new_color;
uniform int USE_COLOR_BUFFER;


// LIGHTING:
uniform mat3 normalMatrix;
uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;
uniform vec4 aLight;
uniform float Shininess;
uniform int addAmbient = 1;
uniform int addDiffuse = 1;
uniform int addSpecular = 1;


void main() 
{


 // normal vector to the surface in eye coordinates
   // vec4 normal4 = vec4(vNormal.xyz, 0.0);
   // vec3 normal = normalize((viewMatrix * modelMatrix * normal4).xyz);
   vec3 normal = normalize(normalMatrix * vNormal);

   // vector towards the eye from the vertex position
   vec4 position4 = camera_view * model_view * vPosition;
   vec3 position = -normalize(position4.xyz);

   // vector towards the light in eye coordinates
   vec3 light;
   if (aLight.w == 0.0)
      // treat light as a direction
      light = normalize(aLight.xyz);
   else
      // treat light as a position
      light = normalize(aLight.xyz - position);
   vec4 light4 = camera_view * vec4(light.xyz, 0.0);
   light = normalize(light4.xyz);

    // halfway vector
   vec3 halfway = normalize(position + light);

   // ambient reflection
   vec4 ambient = AmbientProduct;

   // diffuse reflection
   float diffuseAttenuation = max(dot(light, normal), 0.0);
   vec4 diffuse =  diffuseAttenuation * DiffuseProduct;

   // specular reflection
   vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
   if (diffuseAttenuation > 0.0) {
      float specularAttenuation = 0.0;
      float spec = max(dot(normal, halfway), 0.0);
      if (spec > 0.0)
         specularAttenuation = pow(spec,Shininess);
      specular = max(specularAttenuation * SpecularProduct, 0.0);
   }

    vec3 color3; // 3 components of color as vec4
    
    // flag to switch between the solid color, or gradients
    if(USE_COLOR_BUFFER == 1){
        color3 = vec3(vColor.x, vColor.y, vColor.z); // vertex buffer color vColor as vec4
    } else {
        color3 = vec3(new_color.x, new_color.y, new_color.z); // solid uniform new_color as uniform vec4
    }

   // color of this vertex
   if (addAmbient==1) color3 += ambient.xyz;
   if (addDiffuse==1) color3 += diffuse.xyz;
   if (addSpecular==1) color3 += specular.xyz;
   color = vec4(color3, 1.0); // out vec4

    	// model_view matrix {object.view * object.model}
        // camera_view controls the entire world view and 
        // is only changed by the camera.. 
        //      (thetas change in application program)
    gl_Position =  projection * camera_view * model_view * vPosition;


        // new_color is used for solid colors
        // vColor is used for setting color 
        //  from array of colors


    texCoord  = vTexCoord;

} 
