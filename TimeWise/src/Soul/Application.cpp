#include "Application.h"

#include <Other/Logger.h>
#include <Other/MemoryManager.h>
#include <Utility/Macros.h>
#include <Strings/String.h>
#include <Utility/Timer.h>

namespace Soul
{
	Application::Application() :
		m_Running(true),
		m_Timer(),
		m_AccumulatedMilliseconds(0.0f)
	{
		MemoryManager::Allocate(Megabytes(16));
		
		m_Window = Partition(sf::RenderWindow, sf::VideoMode(1280, 720), "TimeWise", sf::Style::Close);

		m_FontManager = Partition(FontManager, 5);
		m_SoundManager = Partition(SoundManager, 32);
		m_TextureManager = Partition(TextureManager, 64);
		m_InputManager = Partition(InputManager, 2);
	}

	Application::~Application()
	{
		MemoryManager::FreeMemory(m_Window);

		MemoryManager::FreeMemory(m_FontManager);
		MemoryManager::FreeMemory(m_SoundManager);
		MemoryManager::FreeMemory(m_TextureManager);
		MemoryManager::FreeMemory(m_InputManager);

		Assert(MemoryManager::GetTotalPartitionedMemory() == 0);
		MemoryManager::Deallocate();
	}

	void Application::Run()
	{
		m_InputManager->AddController(-1);
		sf::Sprite sprite;
		sprite.setTexture(*m_TextureManager->RequestTexture("res/player.png"));

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
				m_InputManager->Update();
				if (m_InputManager->WasButtonPressed(-1, "Right"))
				{
					SoulLogInfo("Cool!");
				}

				m_AccumulatedMilliseconds -= 6.94f;
			}

			// Rendering
			m_Window->clear();
			
			m_Window->draw(sprite);

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