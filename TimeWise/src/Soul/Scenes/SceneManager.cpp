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

	void SceneManager::Update(float dt, Context& context)
	{
		if (m_QuitScene)
		{
			m_CurrentScene = nullptr;
			m_NextScene = nullptr;
			
			return;
		}

		if (m_NextScene.Raw())
		{
			m_CurrentScene = std::move(m_NextScene);
		}

		if (m_CurrentScene.Raw())
		{
			m_CurrentScene->Update(dt, context);
		}
	}

	void SceneManager::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_CurrentScene.Raw())
		{
			m_CurrentScene->Draw(target, states);
		}
	}

	void SceneManager::ChangeScenes(Scene* scene)
	{
		m_NextScene = scene;
	}

	void SceneManager::Quit()
	{
		m_QuitScene = true;
	}

	bool SceneManager::HasScenes()
	{
		return m_CurrentScene.Raw() || m_NextScene.Raw();
	}
}