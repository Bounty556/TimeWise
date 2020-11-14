#include "ControlsMap.h"

#include <new>

#include <Other/Logger.h>
#include <Other/MemoryManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	ControlsMap::Input::Input() :
		KeyboardKey(-1),
		MouseButton(-1),
		ControllerButton(-1),
		Axis(-1),
		State(ControlsMap::ButtonState::None),
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

			if (input.Axis != -1 && m_ControllerId != -1)
			{
				input.AxisPosition = sf::Joystick::getAxisPosition(m_ControllerId, (sf::Joystick::Axis)input.Axis);
			}
			else
			{
				input.AxisPosition = 0;
			}

			// Are mouse, keyboard, or controller pressed
			if ((input.KeyboardKey != -1 &&
				sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.KeyboardKey) && m_ControllerId == -1) ||
				(input.MouseButton != -1 &&
				sf::Mouse::isButtonPressed((sf::Mouse::Button)input.MouseButton) && m_ControllerId == -1) ||
				(input.ControllerButton != -1 &&
				sf::Joystick::isButtonPressed(m_ControllerId, input.ControllerButton)) ||
				(input.Axis != -1 && Math::Abs(input.AxisPosition) > 70.0f))
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

	void ControlsMap::ClearControls()
	{
		m_Controls.Clear();
	}
}