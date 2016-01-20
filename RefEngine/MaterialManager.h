#pragma once

#include "graphics/Material.h"

#include <memory>

namespace reng 
{

class AssetManager;
struct MaterialDefinition;

struct MaterialDefinition
{
    MaterialDefinition(const char* a_vertexShaderName, const char* a_fragmentShaderName, const char* a_textureName=nullptr) :
        vertexShaderName(a_vertexShaderName),
        fragmentShaderName(a_fragmentShaderName),
        textureName(a_textureName)
    {}

    const char* vertexShaderName;
    const char* fragmentShaderName;
    const char* textureName;
};


class MaterialManager 
{
public:
    static std::shared_ptr<Material> LoadMaterial(AssetManager* pAssetManager, const MaterialDefinition& materialDefinition);
};

}