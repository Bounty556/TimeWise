#pragma once

#include <Other/Logger.h>
#include <Memory/MemoryManager.h>
#include <ResourceManagers/TextureManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	class TextureManagerTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(RequestInvalidTexture);
			RunTest(RequestValidTexture);
			RunTest(ClearAllTextures);
		}

	private:
		static void RequestInvalidTexture()
		{
			TextureManager manager(3);

			const sf::Texture* result = manager.RequestTexture("fakeTexture");

			Assert(result == nullptr);
		}

		static void RequestValidTexture()
		{
			TextureManager manager(3);
			const sf::Texture* result = manager.RequestTexture("res/player.png");
			const sf::Texture* otherTexture = manager.RequestTexture("res/player.png");

			Assert(manager.Count() == 1);
			Assert(result != nullptr);
			Assert(otherTexture == result);
		}

		static void ClearAllTextures()
		{
			TextureManager manager(3);
			manager.RequestTexture("res/player.png");
			Assert(manager.Count() == 1);
			manager.ClearAllTextures();
			Assert(manager.Count() == 0);
		}
	};
}