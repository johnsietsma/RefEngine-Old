#version 410

in vec2 vTexCoord;

uniform sampler2D tex;

out vec4 outputColor;


void main()
{
   outputColor = texture( tex, vTexCoord );
   //outputColor = vec4(vTexCoord, 0.0, 1.0);
}
