#pragma once

#include <SFML/Window/Event.hpp>

#include <Files/ControlsFile.h>
#include <Input/ControlsMap.h>

namespace Soul
{
	/*
	This is the main class that represents a single user's input. This is generally managed by
	the InputManager, but here is a typical use case for the controller:

	Controller controller; // By default, this will load guestControls.controls into controller
	                          -1
	Controller controller1(0, "res/player1Controls.controls");

	// Main game loop
	while (...)
	{
		...
		controller.UpdateInputInfo();
		controller1.UpdateInputInfo();

		if (controller.GetInputInfo().State & ControlsMap::Button::Pressed)
		{
			SoulLogInfo("Button was pressed!");
		}

		if (Math::Abs(controller1.GetInputInfo().AxisPosition) > 50.0f)
		{
			SoulLogInfo("Axis was tilted!");
		}
	}
	*/
	class Controller
	{
	public:
		struct InputInfo
		{
			ControlsMap::ButtonState State;
			float AxisPosition;
		};

	public:
		Controller(int controller = -1, const char* controlsProfile = "res/guestControls.controls");

		Controller(Controller&& otherController); // Move constructor

		/*
		Used for checking for any input when recording input to update a control mapping.
		*/
		void ProcessInput(sf::Event& e);

		/*
		Sets the next input value as a mapping for this control.
		*/
		void RecordInput(const char* controlString);

		/*
		Updates the states of all controls that this controller uses.
		*/
		void UpdateInputInfo();

		// TODO: void SetControlsProfile();

		/*
		Sets the input mapping for a specific control and input origin.
		*/
		void SetInputMapping(const char* controlString, char inputOrigin, int inputValue);

		/*
		Sets the controller that this should listen for input from.
		*/
		void SetControllerId(int controllerId);

		/*
		Returns the state and axis position for a given input.
		*/
		InputInfo GetInputInfo(const char* controlString) const;
	
		/*
		Gets the Id this controller listens for input from.
		*/
		int GetControllerId() const;

	private:
		/*
		Loads the controls from the .controls file to the controls map.
		*/
		void ReloadControls();

	private:
		/*
		Whether this controller is looking for input to update a control profile.
		*/
		bool m_IsRecordingInput;

		/*
		The mapping that this controller is looking for input from.
		*/
		String m_RecordedMapping;

		/*
		The file associated with this controller's profile.
		*/
		ControlsFile m_ControlsFile;

		/*
		The control mappings for this controller.
		*/
		ControlsMap m_ControlsMap;

		/*
		The ID of the controller that this class is checking for input from.
		*/
		int m_ControllerId;
	};
}