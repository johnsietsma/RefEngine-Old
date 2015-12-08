#include "OpenGLRenderer.h"

#include "Mesh.h"

using namespace reng;

void OpenGLRenderer::UseProgram( ProgramId programId )
{
	if (m_state.programId != programId) {
		glUseProgram(programId.Value());
		m_state.programId = programId;
	}
}

void OpenGLRenderer::Bind( const Mesh& mesh )
{
	if (m_state.vaoId != mesh.vaoId) {
		glBindVertexArray(mesh.vaoId.Value());
		m_state.vaoId = mesh.vaoId;
	}

	glBindVertexArray(mesh.vaoId.Value());

	if (mesh.iboId == IBOId_Invalid) {
		if (m_state.vboId != mesh.vboId) {
			glBindBuffer(GL_ARRAY_BUFFER, mesh.vboId.Value());
			m_state.vboId = mesh.vboId;
		}
	}
	else {
		if (m_state.iboId != mesh.iboId) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.iboId.Value());
			m_state.iboId = mesh.iboId;
		}
	}
}

void OpenGLRenderer::Draw(const Mesh& mesh )
{
	if (mesh.iboId == IBOId_Invalid) {
		glDrawArrays(GL_TRIANGLES, 0, 3 * mesh.numberOfVerts);
	}
	else {
		glDrawElements(GL_TRIANGLES, mesh.numberOfIndices, mesh.indexType, 0);
	}
}

void OpenGLRenderer::UnbindAll()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_state.vboId = VBOId_Invalid;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_state.iboId = IBOId_Invalid;

	glBindVertexArray(0);
	m_state.vaoId = VAOId_Invalid;
}


void OpenGLRenderer::UnuseProgram(){
	glUseProgram(0);
	m_state.programId = ProgramId_Invalid;
}
