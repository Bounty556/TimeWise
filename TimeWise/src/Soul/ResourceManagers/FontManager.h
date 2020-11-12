#pragma once

#include <SFML/Graphics/Font.hpp>

#include <Strings/String.h>
#include <Structures/Map.h>

#define FontMap Map<String, sf::Font*>

namespace Soul
{
	class FontManager
	{
	public:
		FontManager(unsigned int capacity = 32);
		FontManager(const FontManager&) = delete;
		FontManager(FontManager&&) = delete;

		~FontManager();

		FontManager& operator=(const FontManager&) = delete;

		/*
		Tries to return an already-loaded Font file if it exists. If it does not exist, the
		provided Font file will attempt to be loaded into memory. If this manager is already
		full of Fonts, this will return nullptr.
		*/
		const sf::Font* RequestFont(const char* fontName);

		/*
		Clears out all currently stored Fonts.
		*/
		void ClearAllFonts();

		/*
		Gets the current number of Fonts that are stored in this manager.
		*/
		unsigned int Count() const;

		/*
		Gets the maximum number of Fonts that can be stored in this manager.
		*/
		unsigned int Capacity() const;

	private:
		/*
		A map of String-Font pairs which stores all currently loaded Fonts.
		*/
		FontMap m_FontMap;

		/*
		The maximum number of Fonts that can be stored in this Font Map.
		*/
		unsigned int m_Capacity;
	};
}