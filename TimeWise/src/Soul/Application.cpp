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
			String toAdd8("Test8!");
			String toAdd9("Test9!");
			String toAdd0("Test0!");
			String toAdd10("Test10!");
			String toAdd11("Test11!");
			String toAdd12("Test12!");
			
			stringMap.AddPair(Math::HashString("1"), toAdd);
			stringMap.AddPair(Math::HashString("2"), toAdd2);
			stringMap.AddPair(Math::HashString("3"), toAdd3);
			stringMap.AddPair(Math::HashString("4"), toAdd4);
			stringMap.AddPair(Math::HashString("5"), toAdd5);
			stringMap.AddPair(Math::HashString("6"), toAdd6);
			stringMap.AddPair(Math::HashString("7"), toAdd7);
			stringMap.AddPair(Math::HashString("8"), toAdd8);
			stringMap.AddPair(Math::HashString("9"), toAdd9);
			stringMap.AddPair(Math::HashString("0"), toAdd0);
			stringMap.AddPair(Math::HashString("10"), toAdd10);
			stringMap.AddPair(Math::HashString("11"), toAdd11);
			stringMap.AddPair(Math::HashString("12"), toAdd12);

			SoulLogInfo("Value at %lld: %s", Math::HashString("1"), stringMap.Get(Math::HashString("1"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("2"), stringMap.Get(Math::HashString("2"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("3"), stringMap.Get(Math::HashString("3"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("4"), stringMap.Get(Math::HashString("4"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("5"), stringMap.Get(Math::HashString("5"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("6"), stringMap.Get(Math::HashString("6"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("7"), stringMap.Get(Math::HashString("7"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("8"), stringMap.Get(Math::HashString("8"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("9"), stringMap.Get(Math::HashString("9"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("0"), stringMap.Get(Math::HashString("0"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("11"), stringMap.Get(Math::HashString("11"))->GetCString());
			SoulLogInfo("Value at %lld: %s", Math::HashString("12"), stringMap.Get(Math::HashString("12"))->GetCString());

			timer.Stop();
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