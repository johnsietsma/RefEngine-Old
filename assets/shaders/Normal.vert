#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec4 normal;

out vec4 vPosition;
out vec4 vNormal;

uniform mat4 projectionView;

void main()
{
    vNormal = normal;
    vPosition = position;
    gl_Position = projectionView * position;
}
