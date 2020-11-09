#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <Strings/String.h>
#include <Utility/Map.h>

#define TextureMap Map<String, sf::Texture*>
#define TextureReferenceMap Map<String, int>

// TODO: Combine texture and reference maps into one?

namespace Soul
{
	/*
	A resource manager class that takes care of loading and unloading textures as they are
	needed
	or no longer used.

	Textures can be requested via RequestTexture(...) which will try to return an already-loaded
	texture file if it exists. If it does not exist, the provided texture file will attempt to
	be loaded into memory. A successful texture request will increase the number of references
	to that texture. Textures will be automatically unloaded once there are no more references
	to that texture.

	References to a texture can be decreased via RemoveTextureReference(...).
	*/
	class TextureManager
	{
	public:
		TextureManager() = delete;

		/*
		Partitions memory for our texture and texture reference maps.
		*/
		static void Init();

		/*
		Tries to return an already-loaded texture file if it exists. If it does not exist, the
		provided texture file will attempt to be loaded into memory. A successful texture
		request will increase the number of references to that texture.
		*/
		static const sf::Texture* RequestTexture(const char* textureName);

		/*
		Removes a reference to a texture. Textures will be automatically unloaded once there are
		no more references to that texture.
		*/
		static void RemoveTextureReference(const char* textureName);

		/*
		Frees the memory that all of the loaded textures have occupied, as well as the texture
		and texture reference maps.
		*/
		static void CleanUp();

	private:
		/*
		A map of String-Texture pairs which stores all currently loaded textures.
		*/
		static TextureMap* m_TextureMap;

		/*
		A map of String-int pairs which keeps reference counts to all currently loaded textures.
		*/
		static TextureReferenceMap* m_TextureReferenceMap;
	};
}