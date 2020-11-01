#include "Application.h"

namespace Soul
{
	Application::Application() :
		m_Window(nullptr),
		m_Running(true)
	{

	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		m_Window = new sf::RenderWindow(sf::VideoMode(1280, 720), "TimeWise", sf::Style::Close);

		// Main game loop
		while (m_Running && m_Window->isOpen())
		{
			// Event processing
			ProcessEvents();

			// Update

			// Rendering
			m_Window->clear();
			m_Window->display();
		}

		// Clean up
	}

	void Application::ProcessEvents()
	{
		sf::Event e;
		while (m_Window->pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::KeyPressed:
				{
					if (e.key.code == sf::Keyboard::Escape)
					{
						m_Window->close();
					}
				} break;
			}
		}
	}
}