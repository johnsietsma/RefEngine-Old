#include "GLHelpers.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

string readFile(const char* fileName)
{
	ifstream ifs(fileName, ios::in | ios::binary | ios::ate);
	if (!ifs.is_open()) return "";

	ifstream::pos_type fileSize = ifs.tellg();
	ifs.seekg(0, ios::beg);

	vector<char> bytes((unsigned int)fileSize);
	ifs.read(&bytes[0], fileSize);

	return string(&bytes[0], (unsigned int)fileSize);
}



bool GLHelpers::CheckCompileStatus(GLuint shaderId)
{
	GLint result = GL_FALSE;
	int logLength;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		char* logBuffer = NULL;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		logBuffer = new char[logLength];
		glGetShaderInfoLog(shaderId, logLength, NULL, logBuffer);
		cerr << "Compile Error: " << logBuffer << endl;
		delete[] logBuffer;
		return false;
	}
	return true;
}

bool GLHelpers::CheckLinkStatus(GLuint programId)
{
	GLint result = GL_FALSE;
	int logLength;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		char* logBuffer = NULL;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		logBuffer = new char[logLength];
		glGetProgramInfoLog(programId, logLength, NULL, logBuffer);
		cerr << "Link Error: " << logBuffer << endl;
		delete[] logBuffer;
		return false;
	}
	return true;
}

GLuint GLHelpers::LoadShader(const char* shaderFileName, GLenum shaderType)
{
	GLuint shaderId = glCreateShader(shaderType);
	string shaderSource = readFile(shaderFileName);
	if (shaderSource.length() == 0) {
		cerr << "Can't load ";
		switch (shaderType) {
		case GL_VERTEX_SHADER: cerr << "vertex"; break;
		case GL_FRAGMENT_SHADER: cerr << "fragment"; break;
		default: cerr << shaderType; break;
		}
		cerr << " shader : " << shaderFileName << endl;
		return -1;
	}

	const char* shaderSourceBuffer = shaderSource.c_str();
	glShaderSource(shaderId, 1, &shaderSourceBuffer, NULL);
	glCompileShader(shaderId);

	if (!CheckCompileStatus(shaderId)) {
		return -1;
	}

	return shaderId;

}
