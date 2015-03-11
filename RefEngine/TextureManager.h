#pragma once

#include "OpenGLTypes.h"

#include <map>

class Texture
{
public:
    TextureId m_textureId;
    int width;
    int height;
    int format;
};


// TODO unify with ProgramManager as CachedLoader
class TextureManager
{
public:
	const Texture& GetOrLoadTexture(const char* textureFileName);

private:
    std::map<int,Texture> m_textureMap;

    int GetTextureKey( const char* textureFileName );
    Texture LoadTexture( const char* fileName );
};

