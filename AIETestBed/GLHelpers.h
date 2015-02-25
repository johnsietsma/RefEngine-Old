#pragma once

#include "gl_core_4_4.h"

class GLHelpers
{
public:
	/**
	 * Check the result of a shader compile.
	 * If the compile failed the error will the written to cerr and false returned.
	 * Returns true if the compile succeeded.
	 */
	static bool CheckCompileStatus(GLuint shaderId);

	/**
	* Check the result of shader program linking.
	* If the link failed the error will the written to cerr and false returned.
	* Returns true if the link succeeded.
	*/
	static bool CheckLinkStatus(GLuint programId);

	/**
	 * Load a shader from the given file name, compile it and check for compile errors.
	 * Returns the shader id.
	 */
	static GLuint LoadShader(const char* shaderFileName, GLenum shaderType);

private:
	GLHelpers() {}; // Abstract class
};
