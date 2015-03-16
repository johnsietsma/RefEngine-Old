#include "AssetContainer.h"

#include "CachingFactory.h"
#include "GLHelpers.h"

#include <string>

using namespace reng;

AssetContainer::AssetContainer() :
m_pShaderFactory(new ShaderFactory(GLHelpers::LoadShader)),
m_pProgramFactory(new ProgramFactory(GLHelpers::LinkProgram)),
m_pTextureFactory(new TextureFactory(GLHelpers::LoadTexture))
{}

ShaderId AssetContainer::LoadShader(const char* shaderFileName, ShaderType shaderType)
{
	return m_pShaderFactory->Get(shaderFileName, shaderType);
}

ProgramId AssetContainer::LinkProgram(ShaderId fragmentShaderId, ShaderId vertexShaderId)
{
	return m_pProgramFactory->Get(fragmentShaderId, vertexShaderId);
}

Texture AssetContainer::LoadTexture(const char* fileName)
{
	return m_pTextureFactory->Get(fileName);
}