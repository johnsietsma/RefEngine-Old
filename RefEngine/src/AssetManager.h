#pragma once

#include "OpenGLTypes.h"

#include <string>

namespace reng {

// fwd decls
class Texture;

template<typename TMake, typename...TArgs>
class CachingFactory;

typedef CachingFactory<ShaderId, const char*, ShaderType> ShaderFactory;
typedef CachingFactory<ProgramId, ShaderId, ShaderId> ProgramFactory;
typedef CachingFactory<Texture, const char*> TextureFactory;


/**
 * A simple wrapper around Container to provide cached access to commonly used assets.
 */
class AssetManager
{
public:
	AssetManager();

	ShaderId LoadShader(const char* shaderFileName, ShaderType shaderType);
	ProgramId LinkProgram(ShaderId fragmentShaderId, ShaderId vertexShaderId);
	Texture LoadTexture(const char* fileName);

private:
	ShaderFactory* m_pShaderFactory;
	ProgramFactory* m_pProgramFactory;
	TextureFactory* m_pTextureFactory;
};

}