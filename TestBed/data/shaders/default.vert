#version 410

in vec4 position;

uniform mat4 projectionView;

void main()
{
    gl_Position = projectionView * position;
}
