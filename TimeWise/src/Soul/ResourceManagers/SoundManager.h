#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include <Strings/String.h>
#include <Utility/Map.h>

#define SoundMap Map<String, sf::SoundBuffer*>
#define SoundReferenceMap Map<String, int>

// TODO: Combine sound and reference maps into one?

namespace Soul
{
	class SoundManager
	{
	public:
		SoundManager() = delete;

		static void Init();

		static const sf::SoundBuffer* RequestSound(const char* soundName);

		static void RemoveSoundReference(const char* soundName);

		static void CleanUp();

	private:
		static SoundMap* m_SoundMap;
		static SoundReferenceMap* m_SoundReferenceMap;
	};
}