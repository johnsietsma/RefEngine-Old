#pragma once

#include "graphics/OpenGLTypes.h"
#include "graphics/Texture.h"

#include <string>

namespace reng {

template<typename TMake, typename...TArgs>
class CachingFactory;

typedef CachingFactory<ShaderId, const char*, ShaderType> ShaderFactory;
typedef CachingFactory<ProgramId, ShaderId, ShaderId> ProgramFactory;
typedef CachingFactory<Texture, const char*> TextureFactory;


class BadAssetLoad : public std::runtime_error 
{
public:
	BadAssetLoad(const char* message) : std::runtime_error(message) {}
	BadAssetLoad(const std::string& message) : std::runtime_error(message.c_str()) {}
};

/**
 * A simple wrapper around Container to provide cached access to commonly used assets.
 */
class AssetManager
{
public:
	AssetManager();

	ShaderId LoadShader(const char* shaderFileName, ShaderType shaderType);
	Texture LoadTexture(const char* fileName);

    ProgramId LoadProgram(const char* vertShaderFileName, const char* fragShaderFileName);
    ProgramId LinkProgram(ShaderId fragmentShaderId, ShaderId vertexShaderId);

private:
	ShaderFactory* m_pShaderFactory;
	ProgramFactory* m_pProgramFactory;
	TextureFactory* m_pTextureFactory;
};

}
