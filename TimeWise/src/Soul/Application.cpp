#include "Application.h"

#include <Other/Logger.h>
#include <Other/MemoryManager.h>
#include <Utility/Macros.h>
#include <Strings/String.h>
#include <Utility/Context.h>
#include <Utility/Timer.h>

#include <Scenes/MainMenuScene.h>

// TODO: Make FPS customizable?
namespace Soul
{
	Application::Application() :
		m_Timer(),
		m_AccumulatedMilliseconds(0.0f),
		m_TargetFrameRateMilliseconds(6.94f) // 144 FPS
	{
		MemoryManager::Allocate(Megabytes(16));
		
		m_Window = Partition(sf::RenderWindow, sf::VideoMode(1280, 720), "TimeWise", sf::Style::Close);

		m_DebugDrawer = Partition(DebugDrawer, 32);
		m_FontManager = Partition(FontManager, 4);
		m_SoundManager = Partition(SoundManager, 8);
		m_TextureManager = Partition(TextureManager, 16);
		m_InputManager = Partition(InputManager, 2);
		m_SceneManager = Partition(SceneManager);
	}

	Application::~Application()
	{
		MemoryManager::FreeMemory(m_Window);

		MemoryManager::FreeMemory(m_DebugDrawer);
		MemoryManager::FreeMemory(m_FontManager);
		MemoryManager::FreeMemory(m_SoundManager);
		MemoryManager::FreeMemory(m_TextureManager);
		MemoryManager::FreeMemory(m_InputManager);
		MemoryManager::FreeMemory(m_SceneManager);

		Assert(MemoryManager::GetTotalPartitionedMemory() == 0);
		MemoryManager::Deallocate();
	}

	void Application::Run()
	{
		m_InputManager->AddController(-1);
		m_InputManager->AddController(0);

		Context context{ 1280, 720, *m_DebugDrawer, *m_FontManager, *m_SoundManager, *m_TextureManager, *m_InputManager, *m_SceneManager };

		m_SceneManager->ChangeScenes(Partition(MainMenuScene, context));

		m_Timer.Start();
		while (m_SceneManager->HasScenes())
		{
			m_AccumulatedMilliseconds += m_Timer.GetDeltaTime();
			while (m_AccumulatedMilliseconds >= m_TargetFrameRateMilliseconds)
			{
				m_DebugDrawer->Clear();

				// Event processing
				ProcessEvents();

				// Updating
				m_InputManager->Update();
				m_SceneManager->Update(m_TargetFrameRateMilliseconds, context);

				m_AccumulatedMilliseconds -= m_TargetFrameRateMilliseconds;
			}

			// Rendering
			m_Window->clear();

			m_SceneManager->Draw(*m_Window, sf::RenderStates::Default);
			m_DebugDrawer->Draw(*m_Window, sf::RenderStates::Default);

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
					m_SceneManager->Quit();
				} break;
			
				case sf::Event::KeyPressed:
				{
					if (e.key.code == sf::Keyboard::Escape)
					{
						m_SceneManager->Quit();
					}
				} break;
			}
		}
	}
}