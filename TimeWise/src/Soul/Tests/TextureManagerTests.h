#pragma once

#include <Logging/Logger.h>
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
		}

	private:
		static void RequestInvalidTexture()
		{
			const sf::Texture* result = TextureManager::RequestTexture("fakeTexture");

			Assert(result == nullptr);
		}

		static void RequestValidTexture()
		{
			const sf::Texture* result = TextureManager::RequestTexture("res/opa.jpg");
			const sf::Texture* otherTexture = TextureManager::RequestTexture("res/opa.jpg");

			Assert(result != nullptr);
			Assert(otherTexture == result);

			TextureManager::RemoveTextureReference("res/opa.jpg");
			TextureManager::RemoveTextureReference("res/opa.jpg");
		}
	};
}