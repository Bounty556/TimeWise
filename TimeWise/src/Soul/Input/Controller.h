#pragma once

#include <Files/ControlsFile.h>
#include <Input/ControlsMap.h>

namespace Soul
{
	class Controller
	{
	public:
		Controller(const char* controlsProfile, int controller = -1);

		void ProcessInput();

		void UpdateInputInfo();
		void SetControlsProfile();
		void SetInputMapping(const char* controlString, char inputOrigin, int inputValue);

		void SetControllerId();
		int GetControllerId() const;

		ControlsMap::ButtonState GetInputState(const char* controlString);
		float GetAxis(const char* controlString);

	private:
		/*
		Whether this controller is looking for input to update a control profile.
		*/
		bool m_IsRecordingInput;

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