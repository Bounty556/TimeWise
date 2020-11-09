#include "MusicManager.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	sf::Music* MusicManager::m_Music;
	bool MusicManager::m_DidLoad;

	void MusicManager::Init()
	{
		m_Music = Partition(sf::Music);
		m_DidLoad = false;
	}

	void MusicManager::Load(const char* fileName)
	{
		m_Music->stop();
		m_DidLoad = m_Music->openFromFile(fileName);
	}

	void MusicManager::Start()
	{
		if (m_DidLoad)
		{
			m_Music->play();
		}
	}

	void MusicManager::Stop()
	{
		if (m_DidLoad)
		{
			m_Music->stop();
		}
	}
	void MusicManager::CleanUp()
	{
		Stop();
		MemoryManager::FreeMemory(m_Music);
	}
}