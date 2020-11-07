#pragma once

#include <SFML/Window/Event.hpp>

#include <Input/Controller.h>

namespace Soul
{
	class InputManager
	{
	public:
		InputManager() = delete;

		static void Init();

		static void Update();

		static void ProcessInput(sf::Event& e);

		static void CleanUp();

		static void SetAcceptingNewControllers(bool value);

		static Controller::InputInfo GetInputInfo(unsigned int player, const char* controlString);

	private:
		static Vector<Controller>* m_Controllers;
		static bool m_AcceptingNewControllers;
	};
}