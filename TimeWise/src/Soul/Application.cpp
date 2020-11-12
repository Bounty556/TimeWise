#include "Application.h"

#include <Layers/LayerManager.h>
#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <ResourceManagers/FontManager.h>
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

		FontManager::Init();
		LayerManager::Init();
	}

	Application::~Application()
	{
		MemoryManager::FreeMemory(m_Window);

		LayerManager::CleanUp();
		FontManager::CleanUp();

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
				LayerManager::Update(6.94f);

				m_AccumulatedMilliseconds -= 6.94f;
			}

			// Rendering
			m_Window->clear();
			
			LayerManager::Draw(*m_Window, sf::RenderStates::Default);

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