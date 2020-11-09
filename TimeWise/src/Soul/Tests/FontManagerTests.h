#pragma once

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <ResourceManagers/FontManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	class FontManagerTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(RequestInvalidFont);
			RunTest(RequestValidFont);
		}

	private:
		static void RequestInvalidFont()
		{
			const sf::Font* result = FontManager::RequestFont("fakeFont");

			Assert(result == nullptr);
		}

		static void RequestValidFont()
		{
			const sf::Font* result = FontManager::RequestFont("res/font.otf");
			const sf::Font* otherTexture = FontManager::RequestFont("res/font.otf");

			Assert(result != nullptr);
			Assert(otherTexture == result);

			FontManager::ClearFonts();
		}
	};
}