#pragma once

#include <SFML/Window/Event.hpp>

#include <Files/ControlsFile.h>
#include <Input/ControlsMap.h>

namespace Soul
{
	class Controller
	{
	public:
		struct InputInfo
		{
			ControlsMap::ButtonState State;
			float AxisPosition;
		};

	public:
		Controller(const char* controlsProfile = "res/guestControls.controls", unsigned int controller = 0);

		void ProcessInput(sf::Event& e);

		/*
		Sets the next input value as a mapping for this control.
		*/
		void RecordInput(const char* controlString);

		void UpdateInputInfo();

		// TODO: void SetControlsProfile();

		void SetInputMapping(const char* controlString, char inputOrigin, int inputValue);

		void SetControllerId(int controllerId);

		unsigned int GetControllerId() const;

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
		unsigned int m_ControllerId;
	};
}