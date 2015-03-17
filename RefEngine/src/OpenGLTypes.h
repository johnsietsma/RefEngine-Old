#pragma once

#include "StronglyTyped.h"
#include "gl_core_4_1.h"

//-----------------------------------------------------------------------------
// Create strong types for various OpenGL ids

STRONG_TYPE(GLuint, VAOId, -1)
STRONG_TYPE(GLuint, VBOId, -1)
STRONG_TYPE(GLuint, IBOId, -1)

STRONG_TYPE(GLuint, ShaderId, -1)
HASH_TYPE(GLuint, ShaderId)

STRONG_TYPE(GLuint, ProgramId, -1)
STRONG_TYPE(GLuint, UniformLocationId, -1)

STRONG_TYPE(GLuint, TextureId, -1)

STRONG_TYPE(GLenum, ShaderType, -1)
HASH_TYPE(GLenum, ShaderType)

namespace reng {


const ShaderType FragmentShader = GL_FRAGMENT_SHADER;
const ShaderType VertexShader = GL_VERTEX_SHADER;



//-----------------------------------------------------------------------------
// Map a C numeric type to a GLenum value at compile time

template<typename T> struct GLEnumValue {
	static const int value = -1;
	//static_assert(false, "Unknown OpenGL type");
};

template<> struct GLEnumValue<float> {
	static const int value = GL_FLOAT;
};

template<> struct GLEnumValue<short> {
	static const int value = GL_SHORT;
};

template<> struct GLEnumValue<int> {
	static const int value = GL_INT;
};

template<> struct GLEnumValue<unsigned short> {
	static const int value = GL_UNSIGNED_SHORT;
};

template<> struct GLEnumValue<unsigned int> {
	static const int value = GL_UNSIGNED_INT;
};

}