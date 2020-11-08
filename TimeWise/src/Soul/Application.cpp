#include "Application.h"

#include <Files/ControlsFile.h>
#include <Files/TextFile.h>
#include <Input/ControlsMap.h>
#include <Input/InputManager.h>
#include <Logging/Logger.h>
#include <Utility/Macros.h>
#include <Utility/Math.h>
#include <Utility/Map.h>
#include <Strings/String.h>
#include <Strings/StringReader.h>
#include <Utility/Timer.h>
#include <Utility/Vector.h>
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
		InputManager::Init();
		
		m_Window = Partition(sf::RenderWindow, sf::VideoMode(1280, 720), "TimeWise", sf::Style::Close);

		InputManager::SetAcceptingNewControllers(true);

		// Main game loop
		while (m_Running)
		{
			// Event processing
			ProcessEvents();
			InputManager::Update();

			if (InputManager::GetInputInfo(0, "Jump").State & ControlsMap::Pressed)
			{
				SoulLogInfo("Player 1 Jumped!");
			}

			if (InputManager::GetInputInfo(1, "Jump").State & ControlsMap::Pressed)
			{
				SoulLogInfo("Player 2 Jumped!");
			}

			if (InputManager::GetInputInfo(2, "Jump").State & ControlsMap::Pressed)
			{
				SoulLogInfo("Player 3 Jumped!");
			}

			// Rendering
			m_Window->clear();
			m_Window->display();
		}

		// Clean up
		MemoryManager::FreeMemory(m_Window);
		InputManager::CleanUp();
		MemoryManager::DrawMemory();
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
			InputManager::ProcessInput(e);
		}
	}
}