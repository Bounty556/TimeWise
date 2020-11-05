#include "ControlsMap.h"

#include <new>

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	ControlsMap::Input::Input() :
		InputName(),
		KeyboardKey(-1),
		MouseButton(-1),
		ControllerButton(-1),
		Axis(-1),
		State(ButtonState::None),
		AxisPosition(0.0f)
	{
	}

	ControlsMap::ControlsMap(const char* inputString, unsigned int inputs) :
		m_ControlsCount(inputs),
		m_Controls(PartitionArray(Input, inputs)),
		m_ControllerId(-1)
	{
		Assert(m_Controls);

		// Put all of the inputs into the array, initialize values
		for (unsigned int character = 0, i = 0; i < m_ControlsCount; ++i)
		{
			new (m_Controls + i) Input();

			while (inputString[character] != ',' && inputString[character] != ';')
			{
				m_Controls[i].InputName += inputString[character];
				++character;
			}

			m_Controls[i].InputName += '\0';

			if (inputString[character] == ',')
			{
				++character;
			}
			else if (inputString[character] == ';' && i != m_ControlsCount - 1)
			{
				SoulLogError("Incorrect number of inputs (%d) passed with input string (%s)", inputs, inputString);
				Assert(false);
			}
		}
	}

	ControlsMap::~ControlsMap()
	{
		MemoryManager::FreeMemory(m_Controls);
	}

	const ControlsMap::Input& ControlsMap::GetInputInfo(const char* input) const
	{
		for (unsigned int i = 0; i < m_ControlsCount; ++i)
		{
			if (m_Controls[i].InputName.CompareTo(input) == 0)
			{
				return m_Controls[i];
			}
		}

		SoulLogError("Unable to find control mapping for input %s", input);
		Assert(false);
		return m_Controls[0];
	}

	void ControlsMap::UpdateInputInfo()
	{
		for (unsigned int i = 0; i < m_ControlsCount; ++i)
		{
			Input& input = m_Controls[i];
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

	void ControlsMap::SetControllerInput(const char* input, unsigned int controllerButton)
	{
		for (unsigned int i = 0; i < m_ControlsCount; ++i)
		{
			if (m_Controls[i].InputName.CompareTo(input) == 0)
			{
				m_Controls[i].Axis = -1;
				m_Controls[i].ControllerButton = controllerButton;
				return;
			}
		}

		SoulLogWarning("Unable to find control mapping for input %s when setting controller input.", input);
	}

	void ControlsMap::SetMouseInput(const char* input, sf::Mouse::Button mouseButton)
	{
		for (unsigned int i = 0; i < m_ControlsCount; ++i)
		{
			if (m_Controls[i].InputName.CompareTo(input) == 0)
			{
				m_Controls[i].KeyboardKey = -1;
				m_Controls[i].MouseButton = (int)mouseButton;
				return;
			}
		}

		SoulLogWarning("Unable to find control mapping for input %s when setting mouse input.", input);
	}

	void ControlsMap::SetKeyboardInput(const char* input, sf::Keyboard::Key keyboardKey)
	{
		for (unsigned int i = 0; i < m_ControlsCount; ++i)
		{
			if (m_Controls[i].InputName.CompareTo(input) == 0)
			{
				m_Controls[i].MouseButton = -1;
				m_Controls[i].KeyboardKey = (int)keyboardKey;
				return;
			}
		}

		SoulLogWarning("Unable to find control mapping for input %s when setting keyboard input.", input);
	}

	void ControlsMap::SetControllerAxis(const char* input, sf::Joystick::Axis axis)
	{
		for (unsigned int i = 0; i < m_ControlsCount; ++i)
		{
			if (m_Controls[i].InputName.CompareTo(input) == 0)
			{
				m_Controls[i].ControllerButton = -1;
				m_Controls[i].Axis = axis;
				return;
			}
		}

		SoulLogWarning("Unable to find control mapping for input %s when setting axis input.", input);
	}

	void ControlsMap::SetController(unsigned int controllerId)
	{
		m_ControllerId = controllerId;
	}
}