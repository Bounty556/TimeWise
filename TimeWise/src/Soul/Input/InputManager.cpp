#include "InputManager.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	Vector<Controller>* InputManager::m_Controllers;
	bool InputManager::m_AcceptingNewControllers;

	void InputManager::Init()
	{
		m_Controllers = Partition(Vector<Controller>);
		m_AcceptingNewControllers = false;
	}

	void InputManager::Update()
	{
		for (unsigned int i = 0; i < m_Controllers->Length(); ++i)
		{
			(*m_Controllers)[i].UpdateInputInfo();
		}
	}

	void InputManager::ProcessInput(sf::Event& e)
	{
		if (m_AcceptingNewControllers)
		{
			switch (e.type)
			{
				case sf::Event::KeyPressed:
				{
					for (unsigned int i = 0; i < m_Controllers->Length(); ++i)
					{
						if ((*m_Controllers)[i].GetControllerId() == -1)
						{
							return;
						}
					}

					m_Controllers->Push(std::move(Controller(-1)));

				} break;

				case sf::Event::JoystickButtonPressed:
				{
					for (unsigned int i = 0; i < m_Controllers->Length(); ++i)
					{
						if (e.joystickButton.joystickId == (*m_Controllers)[i].GetControllerId())
						{
							return;
						}
					}

					m_Controllers->Push(std::move(Controller(e.joystickButton.joystickId)));

				} break;

				case sf::Event::JoystickMoved:
				{
					for (unsigned int i = 0; i < m_Controllers->Length(); ++i)
					{
						if (e.joystickMove.joystickId == (*m_Controllers)[i].GetControllerId())
						{
							return;
						}
					}

					m_Controllers->Push(std::move(Controller(e.joystickMove.joystickId)));

				} break;
			}
		}
	}

	void InputManager::CleanUp()
	{
		MemoryManager::FreeMemory(m_Controllers);
	}

	void InputManager::SetAcceptingNewControllers(bool value)
	{
		m_AcceptingNewControllers = value;
	}

	Controller::InputInfo InputManager::GetPlayerInputInfo(unsigned int player, const char* controlString)
	{
		if (player < 0 || player >= m_Controllers->Length())
		{
			Controller::InputInfo inputInfo;
			inputInfo.State = ControlsMap::ButtonState::None;
			inputInfo.AxisPosition = 0.0f;
			return inputInfo;
		}

		return (*m_Controllers)[player].GetInputInfo(controlString);
	}

	Controller::InputInfo InputManager::GetControllerInputInfo(int controller, const char* controlString)
	{
		for (unsigned int i = 0; i < m_Controllers->Length(); ++i)
		{
			if ((*m_Controllers)[i].GetControllerId() == controller)
			{
				return (*m_Controllers)[i].GetInputInfo(controlString);
			}
		}

		Controller::InputInfo inputInfo;
		inputInfo.State = ControlsMap::ButtonState::None;
		inputInfo.AxisPosition = 0.0f;
		return inputInfo;
	}
}