#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <Strings/String.h>
#include <Utility/Map.h>

#define TextureMap Map<String, sf::Texture*>
#define TextureReferenceMap Map<String, int>

// TODO: Combine texture and reference maps into one?

namespace Soul
{
	class TextureManager
	{
	public:
		TextureManager() = delete;

		static void Init();

		static const sf::Texture* RequestTexture(const char* textureName);

		static void RemoveTextureReference(const char* textureName);

		static void CleanUp();

	private:
		static TextureMap* m_TextureMap;
		static TextureReferenceMap* m_TextureReferenceMap;
	};
}