#include "Application.h"

#include <Files/ControlsFile.h>
#include <Files/TextFile.h>
#include <Input/ControlsMap.h>
#include <Input/InputManager.h>
#include <Layers/LayerManager.h>
#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Nodes/Node.h>
#include <ResourceManagers/FontManager.h>
#include <ResourceManagers/TextureManager.h>
#include <ResourceManagers/SoundManager.h>
#include <ResourceManagers/MusicManager.h>
#include <Utility/Macros.h>
#include <Utility/Math.h>
#include <Utility/Map.h>
#include <Strings/String.h>
#include <Strings/StringReader.h>
#include <Utility/Timer.h>
#include <Utility/Vector.h>

#include <Nodes/TextNode.h>

namespace Soul
{
	Application::Application() :
		m_Window(nullptr),
		m_Running(true),
		m_Timer(),
		m_AccumulatedMilliseconds(0.0f)
	{
		MemoryManager::Allocate(Gigabytes(1));

		InputManager::Init();
		TextureManager::Init();
		SoundManager::Init();
		FontManager::Init();
		MusicManager::Init();
		LayerManager::Init();
	}

	Application::~Application()
	{
		MemoryManager::FreeMemory(m_Window);

		LayerManager::CleanUp();
		MusicManager::CleanUp();
		FontManager::CleanUp();
		SoundManager::CleanUp();
		TextureManager::CleanUp();
		InputManager::CleanUp();

		MemoryManager::DrawMemory();
		MemoryManager::Deallocate();
	}

	void Application::Run()
	{
		m_Window = Partition(sf::RenderWindow, sf::VideoMode(1280, 720), "TimeWise", sf::Style::Close);

		TextNode text;
		text.SetText("This is a test!");
		text.SetColor(sf::Color::White);
		text.SetFont("res/font.otf");

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
				InputManager::Update();

				// Updating
				LayerManager::Update(6.94f);

				m_AccumulatedMilliseconds -= 6.94f;
			}

			// Rendering
			m_Window->clear();
			
			LayerManager::Draw(*m_Window, sf::RenderStates());
			m_Window->draw(text);

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
			InputManager::ProcessInput(e);
		}
	}
}