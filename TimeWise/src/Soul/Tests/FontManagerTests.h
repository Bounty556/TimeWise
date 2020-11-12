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
			RunTest(ClearAllFonts);
		}

	private:
		static void RequestInvalidFont()
		{
			FontManager manager(3);

			const sf::Font* result = manager.RequestFont("fakeFont");

			Assert(result == nullptr);
		}

		static void RequestValidFont()
		{
			FontManager manager(3);
			const sf::Font* result = manager.RequestFont("res/font.otf");
			const sf::Font* otherFont = manager.RequestFont("res/font.otf");

			Assert(manager.Count() == 1);
			Assert(result != nullptr);
			Assert(otherFont == result);
		}

		static void ClearAllFonts()
		{
			FontManager manager(3);
			manager.RequestFont("res/font.otf");
			Assert(manager.Count() == 1);
			manager.ClearAllFonts();
			Assert(manager.Count() == 0);
		}
	};
}