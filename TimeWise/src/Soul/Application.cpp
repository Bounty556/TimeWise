#include "Application.h"

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>
#include <Strings/String.h>
#include <Utility/Timer.h>

namespace Soul
{
	Application::Application() :
		m_Window(nullptr),
		m_Running(true),
		m_Timer(),
		m_AccumulatedMilliseconds(0.0f)
	{
		MemoryManager::Allocate(Megabytes(16));
	}

	Application::~Application()
	{
		MemoryManager::FreeMemory(m_Window);

		Assert(MemoryManager::GetTotalPartitionedMemory() == 0);
		MemoryManager::Deallocate();
	}

	void Application::Run()
	{
		m_Window = Partition(sf::RenderWindow, sf::VideoMode(1280, 720), "TimeWise", sf::Style::Close);

		// Main game loop
		m_Timer.Start();
		while (m_Running)
		{
			// TODO: Make FPS customizable?
			m_AccumulatedMilliseconds += m_Timer.GetDeltaTime();
			while (m_AccumulatedMilliseconds >= 6.94f) // 144 FPS
			{
				// Event processing
				ProcessEvents();

				// Updating

				m_AccumulatedMilliseconds -= 6.94f;
			}

			// Rendering
			m_Window->clear();
			
			m_Window->display();
		}
	}

	void Application::ProcessEvents()
	{
		sf::Event e;
		while (m_Window->pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
				{
					m_Running = false;
				} break;
			
				case sf::Event::KeyPressed:
				{
					if (e.key.code == sf::Keyboard::Escape)
					{
						m_Running = false;
					}
				} break;
			}
		}
	}
}