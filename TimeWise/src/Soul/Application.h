#pragma once

#include <SFML/Graphics.hpp>

#include <ResourceManagers/FontManager.h>
#include <ResourceManagers/SoundManager.h>
#include <ResourceManagers/TextureManager.h>
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

		FontManager* m_FontManager;
		SoundManager* m_SoundManager;
		TextureManager* m_TextureManager;

		bool m_Running;
		Timer m_Timer;
		float m_AccumulatedMilliseconds;
	};
}