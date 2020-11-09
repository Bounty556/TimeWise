#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <ResourceManagers/SoundManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	class SoundManagerTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(RequestInvalidSound);
			RunTest(RequestValidSound);
		}

	private:
		static void RequestInvalidSound()
		{
			const sf::SoundBuffer* result = SoundManager::RequestSound("fakeSound");

			Assert(result == nullptr);
		}

		static void RequestValidSound()
		{
			const sf::SoundBuffer* result = SoundManager::RequestSound("res/sound.ogg");
			const sf::SoundBuffer* otherSound = SoundManager::RequestSound("res/sound.ogg");

			Assert(result != nullptr);
			Assert(otherSound == result);

			SoundManager::RemoveSoundReference("res/sound.ogg");
			SoundManager::RemoveSoundReference("res/sound.ogg");
		}
	};
}