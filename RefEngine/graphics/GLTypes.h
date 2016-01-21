#pragma once

#include "StronglyTyped.h"

#include "graphics/RefEngOpenGl.h"

//-----------------------------------------------------------------------------
// Create strong types for various OpenGL ids

STRONG_TYPE(GLuint, VAOId, GLuint(-1))
STRONG_TYPE(GLuint, VBOId, GLuint(-1))
STRONG_TYPE(GLuint, IBOId, GLuint(-1))

STRONG_TYPE(GLuint, ShaderId, GLuint(-1))
HASH_TYPE(GLuint, ShaderId)

STRONG_TYPE(GLuint, ProgramId, GLuint(-1))
STRONG_TYPE(GLuint, UniformLocationId, GLuint(-1))

STRONG_TYPE(GLuint, TextureId, GLuint(-1))

STRONG_TYPE(GLenum, ShaderType, GLenum(-1))
HASH_TYPE(GLenum, ShaderType)

namespace reng {


const ShaderType FragmentShader = GL_FRAGMENT_SHADER;
const ShaderType VertexShader = GL_VERTEX_SHADER;


}