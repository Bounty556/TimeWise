#pragma once

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
			RunTest(ClearAllSounds);
		}

	private:
		static void RequestInvalidSound()
		{
			SoundManager manager(3);

			const sf::SoundBuffer* result = manager.RequestSound("fakeSound");

			Assert(result == nullptr);
		}

		static void RequestValidSound()
		{
			SoundManager manager(3);
			const sf::SoundBuffer* result = manager.RequestSound("res/sound.ogg");
			const sf::SoundBuffer* otherSound = manager.RequestSound("res/sound.ogg");

			Assert(manager.Count() == 1);
			Assert(result != nullptr);
			Assert(otherSound == result);
		}

		static void ClearAllSounds()
		{
			SoundManager manager(3);
			manager.RequestSound("res/sound.ogg");
			Assert(manager.Count() == 1);
			manager.ClearAllSounds();
			Assert(manager.Count() == 0);
		}
	};
}