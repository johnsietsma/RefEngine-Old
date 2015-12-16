#pragma once

#include "OpenGLTypes.h"


namespace reng {

// Represents an OpenGL texture.
class Texture
{
public:
    TextureId m_textureId;
    int width;
    int height;
    int format;
};


}