#version 410

in vec4 vPosition;
in vec4 vNormal;

out vec4 outputColor;

uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{
   float d = max(0, dot( normalize(vNormal.xyz), lightDirection ) );
   outputColor = vec4(lightColor*d, 1);
}
