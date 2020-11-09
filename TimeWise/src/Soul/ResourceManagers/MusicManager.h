#pragma once

#include <SFML/Audio/Music.hpp>

// TODO: Maybe we could load two music files at once, so we can switch between them seemlessly.

namespace Soul
{
	/*
	A simple singleton wrapper for the sf::Music class. After initialization with Init(), music
	can be loaded via Load(...). As long as the music file was correctly loaded, the Start() and
	Stop() functions will start and stop the music as needed.
	*/
	class MusicManager
	{
	public:
		MusicManager() = delete;

		/*
		Partitions memory from MemoryManager for the music object.
		*/
		static void Init();

		/*
		Attempts to load the provided music file into memory. If failed, Start() and Stop() will
		do nothing.
		*/
		static void Load(const char* fileName);

		/*
		Starts the loaded music file there is any.
		*/
		static void Start();
		
		/*
		Stops the loaded music file there is any.
		*/
		static void Stop();

		/*
		Cleans up memory used for the music object.
		*/
		static void CleanUp();

	private:
		/*
		The music object that stores one chunk of the loaded music file at a time.
		*/
		static sf::Music* m_Music;

		/*
		Did the last requested music file load properly?
		*/
		static bool m_DidLoad;
	};
}