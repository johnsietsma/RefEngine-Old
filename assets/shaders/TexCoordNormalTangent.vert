#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec2 texCoord;
layout(location=2) in vec4 normal;
layout(location=3) in vec4 tangent;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vTagent;
out vec3 vBiTagent;

uniform mat4 projectionView;

void main()
{
    vTexCoord = texCoord;
    vNormal = normal.xyz;
    vTagent = tangent.xyz;
    vBiTagent = cross( vNormal, vTangent ).xyz;
    
    gl_Position = projectionView * position;
}
