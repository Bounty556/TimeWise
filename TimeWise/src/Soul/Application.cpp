#include "Application.h"

#include <Other/Logger.h>
#include <Other/MemoryManager.h>
#include <Utility/Macros.h>
#include <Strings/String.h>
#include <Utility/Context.h>
#include <Utility/Timer.h>

#include <UI/UIContainer.h>
#include <UI/UIComponent.h>
#include <UI/UIButton.h>

namespace Soul
{
	Application::Application() :
		m_Running(true),
		m_Timer(),
		m_AccumulatedMilliseconds(0.0f),
		m_TargetFrameRateMilliseconds(6.94f) // 144 FPS
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

		Context context{ 1280, 720, *m_FontManager, *m_SoundManager, *m_TextureManager, *m_InputManager };

		UIContainer container;

		UIButton* button1 = Partition(UIButton, "Test", context, [] { SoulLogInfo("Hello1"); });
		UIButton* button2 = Partition(UIButton, "Test", context, [] { SoulLogInfo("Hello2"); });
		button2->setPosition(100, 0);
		button1->AddConnection(UIComponent::Right, button2);
		container.AddUIComponent(button1);
		container.AddUIComponent(button2);

		m_Timer.Start();
		while (m_Running)
		{
			// TODO: Make FPS customizable?
			m_AccumulatedMilliseconds += m_Timer.GetDeltaTime();
			while (m_AccumulatedMilliseconds >= m_TargetFrameRateMilliseconds) // 144 FPS
			{
				// Event processing
				ProcessEvents();

				// Updating
				m_InputManager->Update();
				container.Update(m_TargetFrameRateMilliseconds, context);

				m_AccumulatedMilliseconds -= m_TargetFrameRateMilliseconds;
			}

			// Rendering
			m_Window->clear();
			
			container.Draw(*m_Window, sf::RenderStates::Default);

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