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

	Ex:
	InputManager::SetAcceptingNewControllers(true);

	// Game loop
	while (...)
	{
		if (InputManager::GetInputInfo(0, "Jump").State & ControlsMap::Pressed)
		{
			SoulLogInfo("Player 1 Jumped!");
		}
	}
	*/
	class InputManager
	{
	public:
		InputManager() = delete;
		
		/*
		Partitions necessary memory for storing controller information.
		*/
		static void Init();

		/*
		Updates the button states and axis information for all connected controllers.
		*/
		static void Update();

		/*
		Used for determining whether a new controller has connected.
		*/
		static void ProcessInput(sf::Event& e);

		/*
		Frees all necessary memory used for storing controller information.
		*/
		static void CleanUp();

		/*
		Allows the input manager to detect and add newly connected controllers.
		*/
		static void SetAcceptingNewControllers(bool value);

		/*
		Returns an InputInfo struct containing the button information for the desired control
		for a given player.
		*/
		static Controller::InputInfo GetInputInfo(unsigned int player, const char* controlString);

	private:
		/*
		Vector storing all of the controller information for the connected controllers.
		*/
		static Vector<Controller>* m_Controllers;

		/*
		Whether the InputManager should detect and accept newly connected controllers.
		*/
		static bool m_AcceptingNewControllers;
	};
}