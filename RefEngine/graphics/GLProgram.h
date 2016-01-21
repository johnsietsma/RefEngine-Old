#pragma once

#include "GLTypes.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace reng
{

struct GLProgram {
    GLProgram() = delete;


    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, int value);
    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, unsigned int value);
    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, float value);
    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, double value);
    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, glm::vec3 value);
    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, glm::mat4x4 value);
};

}