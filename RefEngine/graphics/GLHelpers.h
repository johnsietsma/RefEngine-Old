#pragma once

#include "graphics/GLTypes.h"
#include "graphics/Texture.h"

namespace reng {

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
	static ShaderId CreateShader(const char* shaderFileName, ShaderType shaderType);

    static void DestroyShader(ShaderId shaderId);

	/**
	 * Link a program with the given shaders and check for link errors.
	 */
	static ProgramId CreateProgram(ShaderId fragmentShaderId, ShaderId vertexShaderId);

    static void DestroyProgram(ProgramId programId);

	/**
	 *  Load a texture from disk and create a new OpenGl texture id.
	 * Returns a Texture structure with image information.
	 */
	static Texture LoadTexture(const char* fileName);

    static void DeleteTexture(Texture texture);


	static void TurnOnDebugLogging();

private:
	GLHelpers() {}; // Abstract class
};

}