#pragma once

#include "StronglyTyped.h"
#include "gl_core_4_1.h"

struct PhantomType_VAO {};
typedef StronglyTyped<GLuint, PhantomType_VAO> VAOId;

struct PhantomType_VBO {};
typedef StronglyTyped<GLuint, PhantomType_VBO> VBOId;

struct PhantomType_Shader {};
typedef StronglyTyped<GLuint, PhantomType_Shader> ShaderId;
const ShaderId ShaderId_Invalid = -1;

struct PhantomType_Program {};
typedef StronglyTyped<GLuint, PhantomType_Program> ProgramId;
const ProgramId ProgramId_Invalid = -1;

struct PhantomType_UniformLocation {};
typedef StronglyTyped<GLuint, PhantomType_UniformLocation> UniformLocationId;
const UniformLocationId UniformLocationId_Invalid = -1;

