#include "MaterialManager.h"

#include "AssetManager.h"
#include "utils/pow2assert.h"

using namespace reng;

std::shared_ptr<Material> MaterialManager::LoadMaterial(AssetManager* pAssetManager, const MaterialDefinition& materialDefinition)
{
    POW2_ASSERT_MSG(materialDefinition.vertexShaderName != nullptr, "A Material must have a vertex shader");
    POW2_ASSERT_MSG(materialDefinition.fragmentShaderName != nullptr, "A Material must have a fragment shader");

    //auto tex = assetManager.LoadTexture("data/textures/Big_pebbles_pxr128.png");

    ProgramId programId = pAssetManager->LoadProgram(materialDefinition.vertexShaderName, materialDefinition.fragmentShaderName);
    auto material = std::make_shared<Material>(programId);

    if (materialDefinition.textureName!=nullptr)
    {
        const Texture& texture = pAssetManager->LoadTexture(materialDefinition.textureName);
        material->SetTexture(texture.textureId, 0);
    }

    return material;
}
