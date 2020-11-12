#include "FontManager.h"

namespace Soul
{
	FontManager::FontManager(unsigned int capacity) :
		m_FontMap(capacity + 1),
		m_Capacity(m_FontMap.GetCapacity() - 1)
	{

	}

	FontManager::~FontManager()
	{
		Vector<sf::Font**> fonts = m_FontMap.GetValues();
		for (unsigned int i = 0; i < fonts.Length(); ++i)
		{
			MemoryManager::FreeMemory(*(fonts[i]));
		}
	}

	const sf::Font* FontManager::RequestFont(const char* fontName)
	{
		// Check to see if the sound is already allocated.
		sf::Font** result = m_FontMap.Get(fontName);

		if (result)
		{
			return *result;
		}
		else
		{
			// Check to make sure we're not full
			if (m_FontMap.GetCount() < m_Capacity)
			{
				sf::Font* font = Partition(sf::Font);
				// If not, allocate a new one and return
				if (font->loadFromFile(fontName))
				{
					m_FontMap.AddPair(fontName, font);
					return *(m_FontMap.Get(fontName));
				}

				MemoryManager::FreeMemory(font);
			}
		}

		return nullptr;
	}

	void FontManager::ClearAllFonts()
	{
		Vector<sf::Font**> fonts = m_FontMap.GetValues();
		for (unsigned int i = 0; i < fonts.Length(); ++i)
		{
			MemoryManager::FreeMemory(*(fonts[i]));
		}

		m_FontMap.Clear();
	}

	unsigned int FontManager::Count() const
	{
		return m_FontMap.GetCount();
	}

	unsigned int FontManager::Capacity() const
	{
		return m_Capacity;
	}
}