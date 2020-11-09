#include "TextureManager.h"

#include <Utility/Macros.h>

namespace Soul
{
	TextureMap* TextureManager::m_TextureMap;
	TextureReferenceMap* TextureManager::m_TextureReferenceMap;

	void TextureManager::Init()
	{
		m_TextureMap = Partition(TextureMap);
		m_TextureReferenceMap = Partition(TextureReferenceMap);
	}

	const sf::Texture* TextureManager::RequestTexture(const char* textureName)
	{
		// Check to see if the texture is already allocated.
		sf::Texture** result = m_TextureMap->Get(textureName);

		if (result)
		{
			// If so, find the already allocated one and increase its reference count
			int& referenceCount = *(m_TextureReferenceMap->Get(textureName));
			++referenceCount;
			return *result;
		}
		else
		{
			// If not, allocated a new one and return
			sf::Texture* texture = Partition(sf::Texture);
			if (!texture->loadFromFile(textureName))
			{
				MemoryManager::FreeMemory(texture);
				return nullptr;
			}
			else
			{
				m_TextureMap->AddPair(textureName, texture);
				m_TextureReferenceMap->AddPair(textureName, 1);
				return texture;
			}
		}
	}

	void TextureManager::RemoveTextureReference(const char* textureName)
	{
		int& referenceCount = *(m_TextureReferenceMap->Get(textureName));
		--referenceCount;

		if (referenceCount <= 0)
		{
			// Delete from both the texture and texture reference maps.
			MemoryManager::FreeMemory(*(m_TextureMap->Get(textureName)));

			m_TextureMap->RemovePair(textureName);
			m_TextureReferenceMap->RemovePair(textureName);
		}
	}

	void TextureManager::CleanUp()
	{
		// We need to manually clean up our texture and reference maps because we stored
		// pointers in them rather than the actual objects.
		Vector<sf::Texture**> textureKeys = m_TextureMap->GetValues();
		for (unsigned int i = 0; i < textureKeys.Length(); ++i)
		{
			MemoryManager::FreeMemory(*textureKeys[i]);
		}

		MemoryManager::FreeMemory(m_TextureMap);
		MemoryManager::FreeMemory(m_TextureReferenceMap);
	}
}