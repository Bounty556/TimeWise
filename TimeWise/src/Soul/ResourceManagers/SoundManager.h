#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include <Strings/String.h>
#include <Utility/Map.h>

#define SoundMap Map<String, sf::SoundBuffer*>

namespace Soul
{
	/*
	A resource manager class that takes care of loading and unloading Sounds as they are needed.

	Sounds can be requested via RequestSound(...) which will try to return an already-loaded
	sound file if it exists. If it does not exist, the provided sound file will attempt to
	be loaded into memory.
	*/
	class SoundManager
	{
	public:
		SoundManager(unsigned int capacity = 32);
		SoundManager(const SoundManager&) = delete;
		SoundManager(SoundManager&&) = delete;

		~SoundManager();

		SoundManager& operator=(const SoundManager&) = delete;

		/*
		Tries to return an already-loaded sound file if it exists. If it does not exist, the
		provided sound file will attempt to be loaded into memory. If this manager is already
		full of sounds, this will return nullptr.
		*/
		const sf::SoundBuffer* RequestSound(const char* soundName);

		/*
		Clears out all currently stored sounds.
		*/
		void ClearAllSounds();

		/*
		Gets the current number of sounds that are stored in this manager.
		*/
		unsigned int Count() const;

		/*
		Gets the maximum number of sounds that can be stored in this manager.
		*/
		unsigned int Capacity() const;

	private:
		/*
		A map of String-SoundBuffer pairs which stores all currently loaded sounds.
		*/
		SoundMap m_SoundMap;

		/*
		The maximum number of sounds that can be stored in this Sound Map.
		*/
		unsigned int m_Capacity;
	};
}