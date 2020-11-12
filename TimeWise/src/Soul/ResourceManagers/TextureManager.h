#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <Strings/String.h>
#include <Utility/Map.h>

#define TextureMap Map<String, sf::Texture>

// TODO: Combine texture and reference maps into one?

namespace Soul
{
	/*
	A resource manager class that takes care of loading and unloading textures as they are
	needed
	or no longer used.

	Textures can be requested via RequestTexture(...) which will try to return an already-loaded
	texture file if it exists. If it does not exist, the provided texture file will attempt to
	be loaded into memory.
	*/
	class TextureManager
	{
	public:
		TextureManager(unsigned int maxTextures = 64);
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;
		
		TextureManager& operator=(const TextureManager&) = delete;

		/*
		Tries to return an already-loaded texture file if it exists. If it does not exist, the
		provided texture file will attempt to be loaded into memory. If this manager is already
		full of textures, this will return nullptr.
		*/
		const sf::Texture* RequestTexture(const char* textureName);

		/*
		Clears out all currently stored textures, invalidating any sprites that were using any of
		these textures.
		*/
		void ClearAllTextures();

		/*
		Gets the current number of textures that are stored in this manager.
		*/
		unsigned int TextureCount() const;

		/*
		Gets the maximum number of textures that can be stored in this manager.
		*/
		unsigned int MaxTextures() const;

	private:
		/*
		A map of String-Texture pairs which stores all currently loaded textures.
		*/
		TextureMap m_TextureMap;

		/*
		The maximum number of textures that can be stored in this Texture Map.
		*/
		unsigned int m_MaxTextures;
	};
}