#version 150
// It was expressed that some drivers required this next line to function properly
precision highp float;

out vec4 colorOut;

in  vec4 outColor;
 
void main(void) {
    colorOut = vec4(outColor);
}
