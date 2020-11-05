#include "Application.h"

#include <Files/TextFile.h>
#include <Input/ControlsMap.h>
#include <Logging/Logger.h>
#include <Utility/Macros.h>
#include <Utility/Math.h>
#include <Utility/String.h>
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
			TextFile file("res/test.controls");

			SoulLogInfo("%s", file.GetCString());

			file.GetString() += "\nI'm adding this on to the end!";

			file.WriteStringToFile();

			MemoryManager::DrawMemory();
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