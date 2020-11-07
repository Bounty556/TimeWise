#pragma once

#include <SFML/Window/Event.hpp>

#include <Files/ControlsFile.h>
#include <Input/ControlsMap.h>

namespace Soul
{
	/*
	This is the main class that represents a single user's input. 
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

		void ProcessInput(sf::Event& e);

		/*
		Sets the next input value as a mapping for this control.
		*/
		void RecordInput(const char* controlString);

		void UpdateInputInfo();

		// TODO: void SetControlsProfile();

		void SetInputMapping(const char* controlString, char inputOrigin, int inputValue);

		void SetControllerId(int controllerId);

		InputInfo GetInputInfo(const char* controlString) const;
	
	private:
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