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
	manager.AddController(-1);

	// Game loop
	while (...)
	{
		if (Manager.WasButtonPressed(0, "Jump"))
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
		Helper functions.
		*/
		bool IsButtonDown(int controller, const char* controlString);
		bool WasButtonPressed(int controller, const char* controlString);
		bool WasButtonReleased(int controller, const char* controlString);
		float AxisPosition(int controller, const char* controlString);

		/*
		Getters
		*/
		unsigned int GetConnectedControllers() const;
		unsigned int GetMaxControllers() const;

	private:
		Controller* m_Controllers;
		unsigned int m_MaxControllers;
		unsigned int m_ConnectedControllers;
	};
}