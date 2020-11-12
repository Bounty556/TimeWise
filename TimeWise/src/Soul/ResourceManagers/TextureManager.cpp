#include "TextureManager.h"

namespace Soul
{
	TextureManager::TextureManager(unsigned int capacity) :
		m_TextureMap(capacity + 1),
		m_Capacity(m_TextureMap.GetCapacity() - 1)
	{

	}

	TextureManager::~TextureManager()
	{
		Vector<sf::Texture**> textures = m_TextureMap.GetValues();
		for (unsigned int i = 0; i < textures.Length(); ++i)
		{
			MemoryManager::FreeMemory(*(textures[i]));
		}
	}

	const sf::Texture* TextureManager::RequestTexture(const char* textureName)
	{
		// Check to see if the texture is already allocated.
		sf::Texture** result = m_TextureMap.Get(textureName);

		if (result)
		{
			return *result;
		}
		else
		{
			// Check to make sure we're not full
			if (m_TextureMap.GetCount() < m_Capacity)
			{
				sf::Texture* texture = Partition(sf::Texture);
				// If not, allocate a new one and return
				if (texture->loadFromFile(textureName))
				{
					m_TextureMap.AddPair(textureName, std::move(texture));
					return *m_TextureMap.Get(textureName);
				}

				MemoryManager::FreeMemory(texture);
			}
		}

		return nullptr;
	}

	void TextureManager::ClearAllTextures()
	{
		Vector<sf::Texture**> textures = m_TextureMap.GetValues();
		for (unsigned int i = 0; i < textures.Length(); ++i)
		{
			MemoryManager::FreeMemory(*(textures[i]));
		}

		m_TextureMap.Clear();
	}

	unsigned int TextureManager::Count() const
	{
		return m_TextureMap.GetCount();
	}

	unsigned int TextureManager::Capacity() const
	{
		return m_Capacity;
	}
}