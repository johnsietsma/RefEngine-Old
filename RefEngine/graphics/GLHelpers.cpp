#include "GLHelpers.h"

#include "graphics/RefEngOpenGL.h"
#include "utils/pow2assert.h"

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace reng;

// ---- Local helpers ----

void APIENTRY openglCallbackFunction(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        // Ignore unknow severity messages to avoid the worst of the spam.
        return;
    }

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

bool GLHelpers::CheckCompileStatus(ShaderId shaderId)
{
	POW2_ASSERT_MSG(glGetShaderiv, "Has OpenGL been initialized?");
	GLint result = GL_FALSE;
	int logLength;
	glGetShaderiv(shaderId.Get(), GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		char* logBuffer = NULL;
		glGetShaderiv(shaderId.Value(), GL_INFO_LOG_LENGTH, &logLength);
		logBuffer = new char[logLength];
		glGetShaderInfoLog(shaderId.Value(), logLength, NULL, logBuffer);
		cerr << "Compile Error: " << logBuffer << endl;
		delete[] logBuffer;
		return false;
	}
	return true;
}

bool GLHelpers::CheckLinkStatus(ProgramId programId)
{
	POW2_ASSERT_MSG(glGetProgramiv, "Has OpenGL been initialized?");
	GLint result = GL_FALSE;
	int logLength;
	glGetProgramiv(programId.Get(), GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		char* logBuffer = NULL;
		glGetProgramiv(programId.Value(), GL_INFO_LOG_LENGTH, &logLength);
		logBuffer = new char[logLength];
		glGetProgramInfoLog(programId.Value(), logLength, NULL, logBuffer);
		cerr << "Link Error: " << logBuffer << endl;
		delete[] logBuffer;
		return false;
	}
	return true;
}

ShaderId GLHelpers::CreateShader(const char* shaderFileName, ShaderType shaderType)
{
	POW2_ASSERT_MSG(glCreateShader, "Has OpenGL been initialized?");
	GLuint shaderId = glCreateShader(shaderType.Value());
	string shaderSource = readFile(shaderFileName);
	if (shaderSource.length() == 0) {
		cerr << "Can't load ";
		if (shaderType == VertexShader) { cerr << "vertex"; }
		else if (shaderType == FragmentShader) { cerr << "fragment"; }
		else { cerr << "unknown"; }
		cerr << " shader : " << shaderFileName << endl;
		return ShaderId_Invalid;
	}

	const char* shaderSourceBuffer = shaderSource.c_str();
	glShaderSource(shaderId, 1, &shaderSourceBuffer, NULL);
	glCompileShader(shaderId);

	if (!CheckCompileStatus(shaderId)) {
        glDeleteShader(shaderId);
		return ShaderId_Invalid;
	}

	return shaderId;

}

void GLHelpers::DestroyShader(ShaderId shaderId)
{
    POW2_ASSERT(shaderId != ShaderId_Invalid);
    glDeleteShader(shaderId.Value());
}

ProgramId GLHelpers::CreateProgram(ShaderId fragmentShaderId, ShaderId vertexShaderId)
{
	if (vertexShaderId == ShaderId_Invalid || fragmentShaderId == ShaderId_Invalid) { return ProgramId_Invalid; }

	// Create the program
	ProgramId programId = glCreateProgram();
	glAttachShader(programId.Value(), vertexShaderId.Value());
	glAttachShader(programId.Value(), fragmentShaderId.Value());
	glLinkProgram(programId.Value());

	if (!GLHelpers::CheckLinkStatus(programId)) {
        glDeleteProgram(programId.Value());
		return ProgramId_Invalid;
	}

    glDetachShader(programId.Value(), vertexShaderId.Value());
    glDetachShader(programId.Value(), fragmentShaderId.Value());

	return programId;
}

void GLHelpers::DestroyProgram(ProgramId programId)
{
    POW2_ASSERT(programId != ProgramId_Invalid);
    glDeleteProgram(programId.Value());
}


Texture GLHelpers::LoadTexture( const char* fileName, unsigned int textureUnit )
{
	Texture texture;
	texture.textureId = TextureId_Invalid;
	unsigned char* data = stbi_load(fileName, &texture.width, &texture.height, &texture.format, STBI_default);
	if( data==nullptr) return texture;

    switch (texture.format)
    {
	case STBI_grey: texture.format = GL_RED; break;
	case STBI_grey_alpha: texture.format = GL_RG; break;
	case STBI_rgb: texture.format = GL_RGB; break;
	case STBI_rgb_alpha: texture.format = GL_RGBA; break;
	default: POW2_ASSERT_FAIL("Unknown texture format: %d", texture.format); return texture;
	};

    glActiveTexture(GL_TEXTURE0 + textureUnit);
	glGenTextures(1, &texture.textureId.Get());
	glBindTexture(GL_TEXTURE_2D, texture.textureId.Value());
	glTexImage2D(GL_TEXTURE_2D, 0, texture.format, texture.width, texture.height, 0, texture.format, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

    delete data;

	return texture;
}

void GLHelpers::DeleteTexture(Texture texture)
{
    const GLuint texIds[1] { texture.textureId.Value() };
    glDeleteTextures(1, texIds);
}

void GLHelpers::TurnOnDebugLogging()
{
    if( glDebugMessageCallback==nullptr ) return;
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openglCallbackFunction, nullptr);
	GLuint unusedIds = 0;
	glDebugMessageControl(
        GL_DONT_CARE, // source
		GL_DONT_CARE, // type
        GL_DONT_CARE, // severity
		0,
		&unusedIds,
		true);
}
