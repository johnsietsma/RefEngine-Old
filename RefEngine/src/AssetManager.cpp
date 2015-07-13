#include "AssetManager.h"

#include "CachingFactory.h"
#include "GLHelpers.h"

#include <exception>
#include <string>

using namespace reng;

AssetManager::AssetManager() :
m_pShaderFactory(new ShaderFactory(GLHelpers::LoadShader)),
m_pProgramFactory(new ProgramFactory(GLHelpers::LinkProgram)),
m_pTextureFactory(new TextureFactory(GLHelpers::LoadTexture))
{}

ShaderId AssetManager::LoadShader(const char* shaderFileName, ShaderType shaderType)
{
	ShaderId shaderId = m_pShaderFactory->Get(shaderFileName, shaderType);
	if (shaderId == ShaderId_Invalid) throw BadAssetLoad(std::string("Failed to load shader ") + shaderFileName);
	return shaderId;
}

ProgramId AssetManager::LinkProgram(ShaderId fragmentShaderId, ShaderId vertexShaderId)
{
	ProgramId programId = m_pProgramFactory->Get(fragmentShaderId, vertexShaderId);
	if (programId == ProgramId_Invalid) throw BadAssetLoad("Failed to load program");
	return programId;
}

Texture AssetManager::LoadTexture(const char* fileName)
{
	Texture texture = m_pTextureFactory->Get(fileName);
	if (texture.m_textureId == TextureId_Invalid) throw BadAssetLoad(std::string("Failed to load texture ") + fileName);
	return texture;
}