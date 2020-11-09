#include "SoundManager.h"

#include <Utility/Macros.h>

namespace Soul
{
	SoundMap* SoundManager::m_SoundMap;
	SoundReferenceMap* SoundManager::m_SoundReferenceMap;

	void SoundManager::Init()
	{
		m_SoundMap = Partition(SoundMap);
		m_SoundReferenceMap = Partition(SoundReferenceMap);
	}

	const sf::SoundBuffer* SoundManager::RequestSound(const char* soundName)
	{
		// Check to see if the sound is already allocated.
		sf::SoundBuffer** result = m_SoundMap->Get(soundName);

		if (result)
		{
			// If so, find the already allocated one and increase its reference count
			int& referenceCount = *(m_SoundReferenceMap->Get(soundName));
			++referenceCount;
			return *result;
		}
		else
		{
			// If not, allocated a new one and return
			sf::SoundBuffer* sound = Partition(sf::SoundBuffer);
			if (!sound->loadFromFile(soundName))
			{
				MemoryManager::FreeMemory(sound);
				return nullptr;
			}
			else
			{
				m_SoundMap->AddPair(soundName, sound);
				m_SoundReferenceMap->AddPair(soundName, 1);
				return sound;
			}
		}
	}

	void SoundManager::RemoveSoundReference(const char* soundName)
	{
		int& referenceCount = *(m_SoundReferenceMap->Get(soundName));
		--referenceCount;

		if (referenceCount <= 0)
		{
			// Delete from both the texture and texture reference maps.
			MemoryManager::FreeMemory(*(m_SoundMap->Get(soundName)));

			m_SoundMap->RemovePair(soundName);
			m_SoundReferenceMap->RemovePair(soundName);
		}
	}

	void SoundManager::CleanUp()
	{
		// We need to manually clean up our sound and reference maps because we stored
		// pointers in them rather than the actual objects.
		Vector<sf::SoundBuffer**> soundKeys = m_SoundMap->GetValues();
		for (unsigned int i = 0; i < soundKeys.Length(); ++i)
		{
			MemoryManager::FreeMemory(*soundKeys[i]);
		}

		MemoryManager::FreeMemory(m_SoundMap);
		MemoryManager::FreeMemory(m_SoundReferenceMap);
	}
}