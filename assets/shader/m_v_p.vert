#version 150

// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
in vec3 in_Position;
in vec4 in_Color;
 
// We output the ex_Color variable to the next shader in the chain
out vec4 ex_Color;

// Values that stay constant for the whole mesh.

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main(void) 
{
	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  P * V * M * vec4(in_Position, 1);
	
	// Pass the color on to the fragment shader
	ex_Color = in_Color;
}
