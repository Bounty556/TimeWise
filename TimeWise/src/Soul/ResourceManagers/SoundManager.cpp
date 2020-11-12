#include "SoundManager.h"

namespace Soul
{
	SoundManager::SoundManager(unsigned int capacity) :
		m_SoundMap(capacity + 1),
		m_Capacity(m_SoundMap.GetCapacity() - 1)
	{

	}

	SoundManager::~SoundManager()
	{
		Vector<sf::SoundBuffer**> buffers = m_SoundMap.GetValues();
		for (unsigned int i = 0; i < buffers.Length(); ++i)
		{
			MemoryManager::FreeMemory(*(buffers[i]));
		}
	}

	const sf::SoundBuffer* SoundManager::RequestSound(const char* soundName)
	{
		// Check to see if the sound is already allocated.
		sf::SoundBuffer** result = m_SoundMap.Get(soundName);

		if (result)
		{
			return *result;
		}
		else
		{
			// Check to make sure we're not full
			if (m_SoundMap.GetCount() < m_Capacity)
			{
				sf::SoundBuffer* soundBuffer = Partition(sf::SoundBuffer);
				// If not, allocate a new one and return
				if (soundBuffer->loadFromFile(soundName))
				{
					m_SoundMap.AddPair(soundName, soundBuffer);
					return *(m_SoundMap.Get(soundName));
				}

				MemoryManager::FreeMemory(soundBuffer);
			}
		}

		return nullptr;
	}

	void SoundManager::ClearAllSounds()
	{
		Vector<sf::SoundBuffer**> buffers = m_SoundMap.GetValues();
		for (unsigned int i = 0; i < buffers.Length(); ++i)
		{
			MemoryManager::FreeMemory(*(buffers[i]));
		}

		m_SoundMap.Clear();
	}

	unsigned int SoundManager::Count() const
	{
		return m_SoundMap.GetCount();
	}

	unsigned int SoundManager::Capacity() const
	{
		return m_Capacity;
	}
}