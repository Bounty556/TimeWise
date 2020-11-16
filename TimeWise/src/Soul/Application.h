#pragma once

#include <SFML/Graphics.hpp>

#include <Input/InputManager.h>
#include <Other/DebugDrawer.h>
#include <ResourceManagers/FontManager.h>
#include <ResourceManagers/SoundManager.h>
#include <ResourceManagers/TextureManager.h>
#include <Scenes/SceneManager.h>
#include <Utility/Timer.h>

namespace Soul
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void ProcessEvents();

	private:
		sf::RenderWindow* m_Window;

		DebugDrawer* m_DebugDrawer;
		FontManager* m_FontManager;
		SoundManager* m_SoundManager;
		TextureManager* m_TextureManager;
		InputManager* m_InputManager;
		SceneManager* m_SceneManager;

		Timer m_Timer;
		float m_AccumulatedMilliseconds;

		float m_TargetFrameRateMilliseconds;
	};
}