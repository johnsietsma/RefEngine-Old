#version 410
in vec3 vertexPosition_modelSpace;
uniform mat4 MVP;

void main()
{
	vec4 v = vec4(vertexPosition_modelSpace,1);
    gl_Position = MVP * v;
}
