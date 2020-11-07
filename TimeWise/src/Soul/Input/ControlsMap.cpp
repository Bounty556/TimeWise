#include "ControlsMap.h"

#include <new>

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	ControlsMap::Input::Input() :
		KeyboardKey(-1),
		MouseButton(-1),
		ControllerButton(-1),
		Axis(-1),
		State(ButtonState::None),
		AxisPosition(0.0f)
	{
	}

	ControlsMap::ControlsMap() :
		m_Controls(),
		m_ControllerId(-1)
	{

	}

	void ControlsMap::AddInput(const char* controlString, Input input)
	{
		m_Controls.AddPair(String(controlString), input);
	}

	const ControlsMap::Input& ControlsMap::GetInputInfo(const char* input) const
	{
		return *(m_Controls.Get(String(input)));
	}

	void ControlsMap::UpdateInputInfo()
	{
		Vector<Input*> inputs = m_Controls.GetValues();

		for (unsigned int i = 0; i < inputs.Length(); ++i)
		{
			Input& input = *(inputs[i]);

			// Are mouse, keyboard, or controller pressed
			if ((input.KeyboardKey != -1 &&
				sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.KeyboardKey)) ||
				(input.MouseButton != -1 &&
				sf::Mouse::isButtonPressed((sf::Mouse::Button)input.MouseButton)) ||
				(input.ControllerButton != -1 &&
				sf::Joystick::isButtonPressed(m_ControllerId, input.ControllerButton)))
			{
				if (input.State & ButtonState::None)
				{
					input.State = (ButtonState)(ButtonState::Pressed | ButtonState::Held);
				}
				else if (input.State & ButtonState::Pressed)
				{
					input.State = ButtonState::Held;
				}
			}
			else // Neither mouse, keyboard, nor controller are pressed
			{
				if (input.State & ButtonState::Held)
				{
					input.State = (ButtonState)(ButtonState::Released | ButtonState::None);
				}
				else if (input.State & ButtonState::Released)
				{
					input.State = ButtonState::None;
				}
			}
			
			if (input.Axis != -1)
			{
				input.AxisPosition = sf::Joystick::getAxisPosition(m_ControllerId, (sf::Joystick::Axis)input.Axis);
			}
		}
	}

	void ControlsMap::SetControllerInput(const char* controlString, unsigned int controllerButton)
	{
		m_Controls.Get(controlString)->ControllerButton = controllerButton;
		m_Controls.Get(controlString)->Axis = -1;
	}

	void ControlsMap::SetMouseInput(const char* controlString, sf::Mouse::Button mouseButton)
	{
		m_Controls.Get(controlString)->MouseButton = mouseButton;
		m_Controls.Get(controlString)->KeyboardKey = -1;
	}

	void ControlsMap::SetKeyboardInput(const char* controlString, sf::Keyboard::Key keyboardKey)
	{
		m_Controls.Get(controlString)->KeyboardKey = keyboardKey;
		m_Controls.Get(controlString)->MouseButton = -1;
	}

	void ControlsMap::SetControllerAxis(const char* controlString, sf::Joystick::Axis axis)
	{
		m_Controls.Get(controlString)->Axis = axis;
		m_Controls.Get(controlString)->ControllerButton = -1;
	}

	void ControlsMap::SetController(unsigned int controllerId)
	{
		m_ControllerId = controllerId;
	}
}