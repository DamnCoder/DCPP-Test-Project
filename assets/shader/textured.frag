#version 150
// It was expressed that some drivers required this next line to function properly
precision highp float;

out vec4 colorOut;

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 outColor;

// Values that stay constant for the whole mesh.
uniform sampler2D TextureSampler;

void main(void) 
{
	// Output color = color of the texture at the specified UV
	vec4 textureColor = texture( TextureSampler, UV ).rgba;
    colorOut = textureColor * outColor;
}
