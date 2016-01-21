#pragma once

#include "graphics/gl_core_4_4.h"

// Magic to make it safe to include OpenGL headers more then once.
// Needed to make QOpenGLWidget behave correctly.
#define __gl3_h_
#define GL_ARB_shader_objects
