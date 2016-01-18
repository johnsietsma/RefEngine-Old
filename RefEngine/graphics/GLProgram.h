#pragma once

#include "types.h"

#include "utils/pow2assert.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace reng
{

struct GLProgram {
    GLProgram() = delete;

    template<typename T>
    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, const T& value)
    {
        POW2_ASSERT_MSG(false, "Unknown uniform value type.");
    }

    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, const int& value)
    {
        glProgramUniform1i(programId.Value(), locationId.Value(), value);

    }

    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, const uint& value)
    {
        glProgramUniform1ui(programId.Value(), locationId.Value(), value);

    }

    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, const float& value)
    {
        glProgramUniform1f(programId.Value(), locationId.Value(), value);

    }

    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, const double& value)
    {
        glProgramUniform1d(programId.Value(), locationId.Value(), value);

    }

    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, const glm::vec3& value)
    {
        glProgramUniform3fv(programId.Value(), locationId.Value(), 1, glm::value_ptr(value));
        //glUniformMatrix4fv(locationId.Value(), 1, GL_FALSE, glm::value_ptr(value));

    }

    static void SetProgramUniform(ProgramId programId, UniformLocationId locationId, const glm::mat4x4& value)
    {
        glProgramUniformMatrix4fv(programId.Value(), locationId.Value(), 1, GL_FALSE, glm::value_ptr(value));
        //glUniformMatrix4fv(locationId.Value(), 1, GL_FALSE, glm::value_ptr(value));

    }
};

}