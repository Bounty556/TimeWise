#pragma once

#include <SFML/Audio/Music.hpp>

// TODO: Maybe we could load two music files at once, so we can switch between them seemlessly.

namespace Soul
{
	class MusicManager
	{
	public:
		MusicManager() = delete;

		static void Init();

		static void Load(const char* fileName);

		static void Start();
		static void Stop();

		static void CleanUp();

	private:
		static sf::Music* m_Music;
		static bool m_DidLoad;
	};
}