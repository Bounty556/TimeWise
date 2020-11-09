#pragma once

#include <SFML/Window/Event.hpp>

#include <Input/Controller.h>

// TODO: Docs

namespace Soul
{
	/*
	Input manager for the soul engine. Handles adding new controllers automatically when
	detected, and updating input states for each controller.

	When SetAcceptingNewControllers(...) is provided a truthy value, each input that comes from
	a new device will add that device to the list of controllers whose input gets recorded and
	stored. To check for input from any connected device, use GetInputInfo(...), and pass in
	the playerNumber whose input you're checking for. The keyboard counts as a separate player
	from the controllers. Players are numbered automatically by the order in which they are
	added to the controllers list, starting at 0.
	*/
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