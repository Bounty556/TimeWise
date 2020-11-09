#pragma once

#include <SFML/Graphics/Font.hpp>

#include <Strings/String.h>
#include <Utility/Map.h>

#define FontMap Map<String, sf::Font*>

namespace Soul
{
	class FontManager
	{
	public:
		FontManager() = delete;

		/*
		Partitions memory for our font map.
		*/
		static void Init();

		/*
		Tries to return an already-loaded font file if it exists. If it does not exist, the
		provided font file will attempt to be loaded into memory.
		*/
		static const sf::Font* RequestFont(const char* fontName);

		/*
		Frees all currently loaded fonts.
		*/
		static void ClearFonts();

		/*
		Frees the all of the loaded fonts, as well as the font map.
		*/
		static void CleanUp();

	private:
		/*
		A map of String-Font pairs which stores all currently loaded fonts.
		*/
		static FontMap* m_FontMap;
	};
}