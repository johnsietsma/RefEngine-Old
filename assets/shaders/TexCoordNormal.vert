#version 410

layout(location=0) in vec4 position;
layout(location=2) in vec4 normal;
layout(location=7) in vec2 texCoord;

out vec4 vPosition;
out vec4 vNormal;
out vec2 vTexCoord;

uniform mat4 projectionView;

void main()
{
    vNormal = normal;
    vPosition = position;
    vTexCoord = texCoord;
    gl_Position = projectionView * position;
}
