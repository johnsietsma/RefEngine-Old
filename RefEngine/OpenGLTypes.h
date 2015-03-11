#pragma once

#include "StronglyTyped.h"
#include "gl_core_4_1.h"

//-----------------------------------------------------------------------------
// Create strong types for various OpenGL ids

struct PhantomType_VAO {};
typedef StronglyTyped<GLuint, PhantomType_VAO> VAOId;
const VAOId VAOId_Invalid;

struct PhantomType_VBO {};
typedef StronglyTyped<GLuint, PhantomType_VBO> VBOId;
const VBOId VBOId_Invalid;

struct PhantomType_IBO {};
typedef StronglyTyped<GLuint, PhantomType_IBO> IBOId;
const IBOId IBOId_Invalid;

struct PhantomType_Shader {};
typedef StronglyTyped<GLuint, PhantomType_Shader> ShaderId;
const ShaderId ShaderId_Invalid = -1;

struct PhantomType_Program {};
typedef StronglyTyped<GLuint, PhantomType_Program> ProgramId;
const ProgramId ProgramId_Invalid = -1;

struct PhantomType_UniformLocation {};
typedef StronglyTyped<GLuint, PhantomType_UniformLocation> UniformLocationId;
const UniformLocationId UniformLocationId_Invalid = -1;

struct PhantomType_Texture {};
typedef StronglyTyped<GLuint, PhantomType_Texture> TextureId;
const TextureId TextureId_Invalid = -1;

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
