#include "Application.h"

#include <Files/ControlsFile.h>
#include <Files/TextFile.h>
#include <Input/ControlsMap.h>
#include <Input/InputManager.h>
#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Nodes/Node.h>
#include <ResourceManagers/TextureManager.h>
#include <ResourceManagers/SoundManager.h>
#include <Utility/Macros.h>
#include <Utility/Math.h>
#include <Utility/Map.h>
#include <Strings/String.h>
#include <Strings/StringReader.h>
#include <Utility/Timer.h>
#include <Utility/Vector.h>

#include <SFML/Audio/Sound.hpp>

namespace Soul
{
	Application::Application() :
		m_Window(nullptr),
		m_Running(true)
	{
		MemoryManager::Allocate(Gigabytes(1));

		InputManager::Init();
		TextureManager::Init();
		SoundManager::Init();
	}

	Application::~Application()
	{
		MemoryManager::FreeMemory(m_Window);

		SoundManager::CleanUp();
		TextureManager::CleanUp();
		InputManager::CleanUp();

		MemoryManager::Deallocate();
	}

	void Application::Run()
	{
		m_Window = Partition(sf::RenderWindow, sf::VideoMode(1280, 720), "TimeWise", sf::Style::Close);

		InputManager::SetAcceptingNewControllers(true);

		sf::Sprite sprite;
		sprite.setTexture(*(TextureManager::RequestTexture("res/opa.jpg")));

		sf::Sound sound;
		sound.setBuffer(*(SoundManager::RequestSound("res/sound.ogg")));

		sound.play();

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
			InputManager::ProcessInput(e);
		}
	}
}