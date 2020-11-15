#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <Scenes/Scene.h>
#include <Utility/Context.h>

namespace Soul
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void Update(float dt, Context& context);

		void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void ChangeScenes(Scene* nextScene);

	private:
		Scene* m_CurrentScene;
		Scene* m_NextScene;
	};
}