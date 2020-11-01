#pragma once

#include <SFML/Graphics.hpp>

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
	};
}