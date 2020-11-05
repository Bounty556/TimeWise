#include "Application.h"

#include <Input/ControlsMap.h>
#include <Logging/Logger.h>
#include <Utility/Macros.h>
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

		{
			String testToInt("5");
			String testToInt2("5.013f");
			String testToInt3("f");
			String testToInt4("fkj123");
			String testToInt5(".45");
			String testToFloat("5");
			String testToFloat2("5.013f");
			String testToFloat3("f");
			String testToFloat4("fkj123.123");
			int testInt = testToInt.ToInt();
			int testInt2 = testToInt2.ToInt();
			int testInt3 = testToInt3.ToInt();
			int testInt4 = testToInt4.ToInt();
			int testInt5 = testToInt5.ToInt();
			float testFloat = testToFloat.ToFloat();
			float testFloat2 = testToFloat2.ToFloat();
			float testFloat3 = testToFloat3.ToFloat();
			float testFloat4 = testToFloat4.ToFloat();

			SoulLogInfo("Converting %s into an int: %d", testToInt.GetCString(), testInt);
			SoulLogInfo("Converting %s into an int: %d", testToInt2.GetCString(), testInt2);
			SoulLogInfo("Converting %s into an int: %d", testToInt3.GetCString(), testInt3);
			SoulLogInfo("Converting %s into an int: %d", testToInt4.GetCString(), testInt4);
			SoulLogInfo("Converting %s into an int: %d", testToInt5.GetCString(), testInt5);
			SoulLogInfo("Converting %s into an float: %f", testToFloat.GetCString(), testFloat);
			SoulLogInfo("Converting %s into an float: %f", testToFloat2.GetCString(), testFloat2);
			SoulLogInfo("Converting %s into an float: %f", testToFloat3.GetCString(), testFloat3);
			SoulLogInfo("Converting %s into an float: %f", testToFloat4.GetCString(), testFloat4);
		}


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