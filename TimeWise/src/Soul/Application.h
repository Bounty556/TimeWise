#pragma once

#include <SFML/Graphics.hpp>

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
		bool m_Running;
		Timer m_Timer;
		float m_AccumulatedMilliseconds;
		int m_FramesPerSecond;
		float m_FramesPerSecondMilliseconds;
	};
}