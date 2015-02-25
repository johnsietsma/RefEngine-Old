#include "GLHelpers.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


// ---- Local helpers ----

void APIENTRY openglCallbackFunction(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
{

	cout << "---------------------opengl-callback-start------------" << endl;
	cout << "message: " << message << endl;
	cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		cout << "OTHER";
		break;
	}
	cout << endl;

	cout << "id: " << id;
	cout << "severity: ";
	switch (severity){
	case GL_DEBUG_SEVERITY_LOW:
		cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		cout << "HIGH";
		break;
	}
	cout << endl;
	cout << "---------------------opengl-callback-end--------------" << endl;
}

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


// ---- Member functions ----

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

void GLHelpers::TurnOnDebugLogging()
{
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	GLuint unusedIds = 0;
	glDebugMessageControl(GL_DONT_CARE,
		GL_DONT_CARE,
		GL_DONT_CARE,
		0,
		&unusedIds,
		true);
}
