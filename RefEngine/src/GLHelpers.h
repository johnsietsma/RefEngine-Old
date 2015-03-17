#pragma once

#include "OpenGLTypes.h"

namespace reng {

class Texture
{
public:
	TextureId m_textureId;
	int width;
	int height;
	int format;
};


class GLHelpers
{
public:
	/**
	 * Check the result of a shader compile.
	 * If the compile failed the error will the written to cerr and false returned.
	 * Returns true if the compile succeeded.
	 */
	static bool CheckCompileStatus(ShaderId shaderId);

	/**
	* Check the result of shader program linking.
	* If the link failed the error will the written to cerr and false returned.
	* Returns true if the link succeeded.
	*/
	static bool CheckLinkStatus(ProgramId programId);

	/**
	 * Load a shader from the given file name, compile it and check for compile errors.
	 * Returns the shader id.
	 */
	static ShaderId LoadShader(const char* shaderFileName, ShaderType shaderType);

	/**
	 * Link a program with the given shaders and check for link errors.
	 */
	static ProgramId LinkProgram(ShaderId fragmentShaderId, ShaderId vertexShaderId);

	/**
	 *  Load a texture from disk and create a new OpenGl texture id.
	 * Returns a Texture structure with image information.
	 */
	static Texture LoadTexture(const char* fileName);


	static void TurnOnDebugLogging();

private:
	GLHelpers() {}; // Abstract class
};

}