#include "Controller.h"

#include <Utility/Math.h>

namespace Soul
{
	Controller::Controller(int controller, const char* controlsProfile) :
		m_IsRecordingInput(false),
		m_RecordedMapping(),
		m_ControlsFile(controlsProfile),
		m_ControlsMap(),
		m_ControllerId(controller)
	{
		m_ControlsMap.SetController(m_ControllerId);
		ReloadControls();
	}

	Controller::Controller(Controller&& otherController) :
		m_RecordedMapping(std::move(otherController.m_RecordedMapping)),
		m_ControlsFile(std::move(otherController.m_ControlsFile)),
		m_ControlsMap(std::move(otherController.m_ControlsMap)),
		m_ControllerId(otherController.m_ControllerId)
	{

	}

	void Controller::ProcessInput(sf::Event& e)
	{
		if (m_IsRecordingInput)
		{
			switch (e.type)
			{
				case sf::Event::KeyPressed:
				{
					m_ControlsMap.SetKeyboardInput(m_RecordedMapping.GetCString(), e.key.code);
					m_IsRecordingInput = false;
				} break;

				case sf::Event::MouseButtonPressed:
				{
					m_ControlsMap.SetMouseInput(m_RecordedMapping.GetCString(), e.mouseButton.button);
					m_IsRecordingInput = false;
				} break;

				case sf::Event::JoystickButtonPressed:
				{
					if (e.joystickButton.joystickId == m_ControllerId)
					{
						m_ControlsMap.SetControllerInput(m_RecordedMapping.GetCString(), e.joystickButton.button);
						m_IsRecordingInput = false;
					}
				} break;

				case sf::Event::JoystickMoved:
				{
					if (e.joystickMove.joystickId == m_ControllerId && Math::Abs(e.joystickMove.position) > 50.0f)
					{
						m_ControlsMap.SetControllerAxis(m_RecordedMapping.GetCString(), e.joystickMove.axis);
						m_IsRecordingInput = false;
					}
				} break;
			}
		}
	}

	void Controller::UpdateInputInfo()
	{
		m_ControlsMap.UpdateInputInfo();
	}

	void Controller::RecordInput(const char* controlString)
	{
		m_IsRecordingInput = true;
		m_RecordedMapping = controlString;
	}

	void Controller::SetInputMapping(const char* controlString, char inputOrigin, int inputValue)
	{
		switch (inputOrigin)
		{
			case 'k':
			{
				m_ControlsMap.SetKeyboardInput(controlString, (sf::Keyboard::Key)inputValue);
			} break;

			case 'm':
			{
				m_ControlsMap.SetMouseInput(controlString, (sf::Mouse::Button)inputValue);
			} break;

			case 'a':
			{
				m_ControlsMap.SetControllerAxis(controlString, (sf::Joystick::Axis)inputValue);
			} break;

			case 'c':
			{
				m_ControlsMap.SetControllerInput(controlString, inputValue);
			} break;
		}
	}

	void Controller::SetControllerId(int controllerId)
	{
		m_ControllerId = controllerId;
		m_ControlsMap.SetController(controllerId);
	}

	Controller::InputInfo Controller::GetInputInfo(const char* controlString) const
	{
		InputInfo inputInfo;
		const ControlsMap::Input& input = m_ControlsMap.GetInputInfo(controlString);
		
		inputInfo.State = input.State;
		inputInfo.AxisPosition = input.AxisPosition;

		return inputInfo;
	}

	int Controller::GetControllerId() const
	{
		return m_ControllerId;
	}

	void Controller::ReloadControls()
	{
		m_ControlsMap.ClearControls();

		Vector<String*> inputNames = m_ControlsFile.GetInputNames();

		for (unsigned int i = 0; i < inputNames.Length(); ++i)
		{
			ControlsMap::Input input;
			input.KeyboardKey = m_ControlsFile.GetInputValue(inputNames[i]->GetCString(), 'k');
			input.MouseButton = m_ControlsFile.GetInputValue(inputNames[i]->GetCString(), 'm');
			input.Axis = m_ControlsFile.GetInputValue(inputNames[i]->GetCString(), 'a');
			input.ControllerButton = m_ControlsFile.GetInputValue(inputNames[i]->GetCString(), 'c');

			m_ControlsMap.AddInput(inputNames[i]->GetCString(), input);
		}
	}
}