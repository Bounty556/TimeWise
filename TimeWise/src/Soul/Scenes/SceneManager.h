#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <Scenes/Scene.h>
#include <Utility/Context.h>

namespace Soul
{
	/*
	Manages the current scene being played. A scene should be loaded before the main game loop
	using ChangeScenes(...), as the main game loop exits when there are no loaded scenes.

	Scenes are only changed before updating every frame, ensuring nothing is in use while being
	freed.
	*/
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void Update(float dt, Context& context);

		void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

		/*
		Queues the provided scene to be loaded starting the next frame.
		*/
		void ChangeScenes(Scene* nextScene);

		/*
		Clears the current and possibly next scene, exiting the game.
		*/
		void Quit();

		/*
		Returns whether there is a scene currently loaded, or if there is a scene that is ready
		to be loaded.
		*/
		bool HasScenes();

	private:
		Scene* m_CurrentScene;
		Scene* m_NextScene;

		bool m_QuitScene;
	};
}