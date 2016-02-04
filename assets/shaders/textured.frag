#version 410

in vec2 vTexCoord;

uniform sampler2D diffuseSampler;

out vec4 outputColor;


void main()
{
   outputColor = texture( diffuseSampler, vTexCoord );
}
