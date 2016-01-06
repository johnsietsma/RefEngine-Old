#version 410

in vec4 vPosition;
in vec4 vNormal;

out vec4 outputColor;

void main()
{
   float d = max(0, dot( normalize(vNormal.xyz), vec3(0,1,0) ) );
   outputColor = vec4(d,d,d,1);
}
