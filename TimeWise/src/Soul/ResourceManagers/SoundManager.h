#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include <Strings/String.h>
#include <Utility/Map.h>

#define SoundMap Map<String, sf::SoundBuffer*>
#define SoundReferenceMap Map<String, int>

// TODO: Combine sound and reference maps into one?

namespace Soul
{
	/*
	A resource manager class that takes care of loading and unloading sounds as they are
	needed or no longer used.

	Sounds can be requested via RequestSound(...) which will try to return an already-loaded
	sound file if it exists. If it does not exist, the provided sound file will attempt to be
	loaded into memory. A successful sound request will increase the number of references to
	that sound. Sounds will be automatically unloaded once there are no more references to
	that sound.

	References to a sound can be decreased via RemoveSoundReference(...).
	*/
	class SoundManager
	{
	public:
		SoundManager() = delete;

		/*
		Partitions memory for our sound and sound reference maps.
		*/
		static void Init();

		/*
		Tries to return an already-loaded sound file if it exists. If it does not exist, the
		provided sound file will attempt to be loaded into memory. A successful sound
		request will increase the number of references to that sound.
		*/
		static const sf::SoundBuffer* RequestSound(const char* soundName);

		/*
		Removes a reference to a sound. Sounds will be automatically unloaded once there are
		no more references to that sound.
		*/
		static void RemoveSoundReference(const char* soundName);

		/*
		Frees the memory that all of the loaded sounds have occupied, as well as the sound and
		sound reference maps.
		*/
		static void CleanUp();

	private:
		/*
		A map of String-Sound pairs which stores all currently loaded sounds.
		*/
		static SoundMap* m_SoundMap;

		/*
		A map of String-int pairs which keeps reference counts to all currently loaded sounds.
		*/
		static SoundReferenceMap* m_SoundReferenceMap;
	};
}