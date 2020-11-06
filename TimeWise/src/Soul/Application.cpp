#include "Application.h"

#include <Files/TextFile.h>
#include <Input/ControlsMap.h>
#include <Logging/Logger.h>
#include <Utility/Macros.h>
#include <Utility/Math.h>
#include <Utility/Map.h>
#include <Utility/String.h>
#include <Utility/Timer.h>
#include <Memory/MemoryManager.h>

namespace Soul
{
	Application::Application() :
		m_Window(nullptr),
		m_Running(true)
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// Initialization
		MemoryManager::Allocate(Gigabytes(1));
		
		m_Window = Partition(sf::RenderWindow, sf::VideoMode(1280, 720), "TimeWise", sf::Style::Close);

		MemoryManager::DrawMemory();
		{
			Timer timer;

			timer.Start();

			Map<String> stringMap;
			String toAdd("Test!");
			String toAdd2("Test2!");
			String toAdd3("Test3!");
			String toAdd4("Test4!");
			String toAdd5("Test5!");
			String toAdd6("Test6!");
			String toAdd7("Test7!");
			
			stringMap.AddPair(Math::HashString(toAdd), toAdd);
			stringMap.AddPair(Math::HashString(toAdd2), toAdd2);
			stringMap.AddPair(Math::HashString(toAdd3), toAdd3);
			stringMap.AddPair(Math::HashString(toAdd4), toAdd4);
			stringMap.AddPair(Math::HashString(toAdd5), toAdd5);
			stringMap.AddPair(Math::HashString(toAdd6), toAdd6);
			stringMap.AddPair(Math::HashString(toAdd7), toAdd7);

			timer.Start();
			SoulLogInfo("Time elapsed: %lld", timer.GetElapsedMilliseconds());

		}
		MemoryManager::DrawMemory();

		// Main game loop
		while (m_Running)
		{
			// Event processing
			ProcessEvents();

			// Rendering
			m_Window->clear();
			m_Window->display();
		}

		// Clean up
		MemoryManager::FreeMemory(m_Window);
		MemoryManager::Deallocate();
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