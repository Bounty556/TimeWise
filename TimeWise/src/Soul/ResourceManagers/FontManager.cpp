#include "FontManager.h"

namespace Soul
{
	FontMap* FontManager::m_FontMap;

	void FontManager::Init()
	{
		m_FontMap = Partition(FontMap);
	}

	const sf::Font* FontManager::RequestFont(const char* fontName)
	{
		sf::Font** result = m_FontMap->Get(fontName);

		if (!result)
		{
			sf::Font* font = Partition(sf::Font);

			if (!font->loadFromFile(fontName))
			{
				MemoryManager::FreeMemory(font);
				return nullptr;
			}

			m_FontMap->AddPair(fontName, font);

			return font;
		}

		return *result;
	}

	void FontManager::ClearFonts()
	{
		// We need to manually clean up our fonts map because we stored pointers in them rather
		// than the actual objects.
		Vector<sf::Font**> fonts = m_FontMap->GetValues();
		for (unsigned int i = 0; i < fonts.Length(); ++i)
		{
			MemoryManager::FreeMemory(*fonts[i]);
		}

		m_FontMap->Clear();
	}

	void FontManager::CleanUp()
	{
		// We need to manually clean up our fonts map because we stored pointers in them rather
		// than the actual objects.
		Vector<sf::Font**> fonts = m_FontMap->GetValues();
		for (unsigned int i = 0; i < fonts.Length(); ++i)
		{
			MemoryManager::FreeMemory(*fonts[i]);
		}

		MemoryManager::FreeMemory(m_FontMap);
	}
}