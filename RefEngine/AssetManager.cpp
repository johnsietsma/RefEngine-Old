#include "AssetManager.h"

#include "CachingFactory.h"
#include "graphics/GLHelpers.h"

#include <exception>
#include <string>

using namespace reng;

AssetManager::AssetManager() :
m_pShaderFactory(new ShaderFactory(GLHelpers::CreateShader, GLHelpers::DestroyShader)),
m_pProgramFactory(new ProgramFactory(GLHelpers::CreateProgram, GLHelpers::DestroyProgram)),
m_pTextureFactory(new TextureFactory(GLHelpers::LoadTexture, GLHelpers::DeleteTexture))
{}

ShaderId AssetManager::CreateShader(const char* shaderFileName, ShaderType shaderType)
{
	ShaderId shaderId = m_pShaderFactory->Get(shaderFileName, shaderType);
	if (shaderId == ShaderId_Invalid) throw BadAssetLoad(std::string("Failed to load shader ") + shaderFileName);
	return shaderId;
}


Texture AssetManager::LoadTexture(const char* fileName)
{
    Texture texture = m_pTextureFactory->Get(fileName);
    if (texture.m_textureId == TextureId_Invalid) throw BadAssetLoad(std::string("Failed to load texture ") + fileName);
    return texture;
}


ProgramId AssetManager::LoadProgram(const char* vertShaderFileName, const char* fragShaderFileName)
{
    ShaderId vertShader = CreateShader(vertShaderFileName, VertexShader);
    ShaderId redFragShader = CreateShader(fragShaderFileName, FragmentShader);

    return LinkProgram(vertShader, redFragShader);
}


ProgramId AssetManager::LinkProgram(ShaderId fragmentShaderId, ShaderId vertexShaderId)
{
	ProgramId programId = m_pProgramFactory->Get(fragmentShaderId, vertexShaderId);
	if (programId == ProgramId_Invalid) throw BadAssetLoad("Failed to load program");
	return programId;
}

std::shared_ptr<Material> AssetManager::CreateMaterial(ProgramId programId)
{
    return std::make_shared<Material>(programId);
}
