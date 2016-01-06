#pragma once

#include "graphics/GLTypes.h"


namespace reng {

// Represents an OpenGL texture.
class Texture
{
public:
    TextureId textureId;
    int width;
    int height;
    int format;
};


}