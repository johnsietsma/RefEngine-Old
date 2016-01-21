#include "GLProgram.h"

#include "graphics/RefEngOpenGL.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace reng;

void GLProgram::SetProgramUniform(ProgramId programId, UniformLocationId locationId, int value)
{
    glProgramUniform1i(programId.Value(), locationId.Value(), value);

}

void GLProgram::SetProgramUniform(ProgramId programId, UniformLocationId locationId, uint value)
{
    glProgramUniform1ui(programId.Value(), locationId.Value(), value);

}

void GLProgram::SetProgramUniform(ProgramId programId, UniformLocationId locationId, float value)
{
    glProgramUniform1f(programId.Value(), locationId.Value(), value);

}

void GLProgram::SetProgramUniform(ProgramId programId, UniformLocationId locationId, double value)
{
    glProgramUniform1d(programId.Value(), locationId.Value(), value);

}

void GLProgram::SetProgramUniform(ProgramId programId, UniformLocationId locationId, glm::vec3 value)
{
    glProgramUniform3fv(programId.Value(), locationId.Value(), 1, glm::value_ptr(value));
    //glUniformMatrix4fv(locationId.Value(), 1, GL_FALSE, glm::value_ptr(value));

}

void GLProgram::SetProgramUniform(ProgramId programId, UniformLocationId locationId, glm::mat4x4 value)
{
    glProgramUniformMatrix4fv(programId.Value(), locationId.Value(), 1, GL_FALSE, glm::value_ptr(value));
    //glUniformMatrix4fv(locationId.Value(), 1, GL_FALSE, glm::value_ptr(value));

}