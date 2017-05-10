#version 150

// attributes
in vec3 InVertex;
in vec3 InNormal;
in vec2 InUV0;
in vec4 InColor;
 
// We output the outColor variable to the next shader in the chain
out vec4 outColor;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;


void main(void) 
{
    // Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(InVertex, 1);
 
    // Pass the color on to the fragment shader
    outColor = InColor;

    // UV of the vertex. No special space for this one.
	UV = InUV0;
}
