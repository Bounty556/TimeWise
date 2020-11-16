#include "SceneManager.h"

#include <Memory/MemoryManager.h>
#include <Utility/Context.h>

namespace Soul
{
	SceneManager::SceneManager() :
		m_CurrentScene(nullptr),
		m_NextScene(nullptr)
	{

	}

	SceneManager::~SceneManager()
	{
		if (m_CurrentScene)
		{
			MemoryManager::FreeMemory(m_CurrentScene);
		}
		
		if (m_NextScene)
		{
			MemoryManager::FreeMemory(m_NextScene);
		}
	}

	void SceneManager::Update(float dt, Context& context)
	{
		if (m_QuitScene)
		{
			if (m_CurrentScene)
			{
				MemoryManager::FreeMemory(m_CurrentScene);
				m_CurrentScene = nullptr;
			}

			if (m_NextScene)
			{
				MemoryManager::FreeMemory(m_NextScene);
				m_NextScene = nullptr;
			}

			return;
		}

		if (m_NextScene)
		{
			if (m_CurrentScene)
			{
				MemoryManager::FreeMemory(m_CurrentScene);
			}
			m_CurrentScene = m_NextScene;
			m_NextScene = nullptr;
		}

		if (m_CurrentScene)
		{
			m_CurrentScene->Update(dt, context);
		}
	}

	void SceneManager::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_CurrentScene)
		{
			m_CurrentScene->Draw(target, states);
		}
	}

	void SceneManager::ChangeScenes(Scene* scene)
	{
		if (m_NextScene)
		{
			MemoryManager::FreeMemory(m_NextScene);
		}

		m_NextScene = scene;
	}

	void SceneManager::Quit()
	{
		m_QuitScene = true;
	}

	bool SceneManager::HasScenes()
	{
		return m_CurrentScene || m_NextScene;
	}
}