#pragma once

#include <SFML/Window/Event.hpp>

#include <Input/Controller.h>

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
	InputManager manager;
	manager.SetAcceptingNewControllers(true);

	// Game loop
	while (...)
	{
		if (manager.GetInputInfo(0, "Jump").State & ControlsMap::Pressed)
		{
			SoulLogInfo("Player 1 Jumped!");
		}
	}
	*/
	class InputManager
	{
	public:
		InputManager(unsigned int maxControllerCount = 5);
		
		~InputManager();

		/*
		Updates the button states and axis information for all connected controllers.
		*/
		void Update();

		/*
		Adds a new controller to this manager as long as there is room for one.
		*/
		void AddController(int controllerId);

		/*
		Returns an InputInfo struct containing the button information for the desired control
		for a given player.
		*/
		Controller::InputInfo GetPlayerInputInfo(unsigned int player, const char* controlString) const;

		/*
		Returns an InputInfo struct containing the button information for the desired control
		for a given controller id.
		*/
		Controller::InputInfo GetControllerInputInfo(int controller, const char* controlString) const;

		/*
		Gets the number of currently connected controllers.
		*/
		unsigned int GetConnectedControllers() const;

		/*
		Gets the number of maximum number of allowed controllers.
		*/
		unsigned int GetMaxControllers() const;

	private:
		/*
		Vector storing all of the controller information for the connected controllers.
		*/
		Controller* m_Controllers;
		
		/*
		The maximum number of controllers this manager can support.
		*/
		unsigned int m_MaxControllers;

		/*
		Number of currently connected controllers.
		*/
		unsigned int m_ConnectedControllers;

		/*
		Whether we should detect and accept newly connected controllers.
		*/
		bool m_AcceptingNewControllers;
	};
}