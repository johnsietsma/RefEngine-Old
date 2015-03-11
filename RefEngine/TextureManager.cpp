#include "TextureManager.h"
#include "gl_core_4_1.h"
#include "GLHelpers.h"
#include "pow2assert.h"

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <functional>

const Texture& TextureManager::GetOrLoadTexture( const char* textureFileName )
{
	int textureKey = GetTextureKey( textureFileName );
	if( m_textureMap.find(textureKey)!=m_textureMap.end() ) { return m_textureMap[textureKey]; }

	// Cache the texture, even if it's invalid
	m_textureMap[textureKey] = LoadTexture( textureFileName );

	return m_textureMap[textureKey];
}

int TextureManager::GetTextureKey( const char* textureFileName )
{
	std::hash<std::string> hash_fn;
	return hash_fn(textureFileName);
}

Texture TextureManager::LoadTexture( const char* fileName )
{
	Texture texture;
	texture.m_textureId = TextureId_Invalid;
	unsigned char* data = stbi_load(fileName, &texture.width, &texture.height, &texture.format, STBI_default);
	if( data==nullptr) return texture;

    switch (texture.format)
    {
        case STBI_grey: texture.format = GL_RED; break;
		case STBI_grey_alpha: texture.format = GL_RG; break;
        case STBI_rgb: texture.format = GL_RGB; break;
        case STBI_rgb_alpha: texture.format = GL_RGBA; break;
        default: POW2_ASSERT_FAIL("Unknown texture format: %d", texture.format); return texture;
    };

    glGenTextures(1, &texture.m_textureId.Get());
    glBindTexture(GL_TEXTURE_2D, texture.m_textureId.Value());
    glTexImage2D(GL_TEXTURE_2D, 0, texture.format, texture.width, texture.height, 0, texture.format, GL_UNSIGNED_BYTE, data);
    //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
