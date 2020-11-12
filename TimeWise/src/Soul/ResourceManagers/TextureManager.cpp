#include "TextureManager.h"

#include <Utility/Macros.h>

namespace Soul
{
	TextureManager::TextureManager(unsigned int maxTextures) :
		m_TextureMap(maxTextures + 1),
		m_MaxTextures(m_TextureMap.GetCapacity() - 1)
	{

	}

	const sf::Texture* TextureManager::RequestTexture(const char* textureName)
	{
		// Check to see if the texture is already allocated.
		sf::Texture* result = m_TextureMap.Get(textureName);

		if (result)
		{
			// If so, find the already allocated one and increase its reference count
			return result;
		}
		else
		{
			// Check to make sure we're not full
			if (m_TextureMap.GetCount() < m_MaxTextures)
			{
				sf::Texture texture;
				// If not, allocate a new one and return
				if (texture.loadFromFile(textureName))
				{
					m_TextureMap.AddPair(textureName, std::move(texture));
					return m_TextureMap.Get(textureName);
				}
			}
		}

		return nullptr;
	}

	void TextureManager::ClearAllTextures()
	{
		m_TextureMap.Clear();
	}

	unsigned int TextureManager::TextureCount() const
	{
		return m_TextureMap.GetCount();
	}

	unsigned int TextureManager::MaxTextures() const
	{
		return m_MaxTextures;
	}
}