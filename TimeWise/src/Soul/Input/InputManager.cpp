#include "InputManager.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	InputManager::InputManager(unsigned int maxControllerCount) :
		m_Controllers(PartitionArray(Controller, maxControllerCount)),
		m_MaxControllers(maxControllerCount),
		m_ConnectedControllers(0),
		m_AcceptingNewControllers(false)
	{

	}

	InputManager::~InputManager()
	{
		MemoryManager::FreeMemory(m_Controllers);
	}

	void InputManager::Update()
	{
		for (unsigned int i = 0; i < m_ConnectedControllers; ++i)
		{
			m_Controllers[i].UpdateInputInfo();
		}
	}

	void InputManager::AddController(int controllerId)
	{
		if (m_ConnectedControllers == m_MaxControllers)
		{
			return;
		}

		for (unsigned int i = 0; i < m_ConnectedControllers; ++i)
		{
			if (m_Controllers[i].GetControllerId() == controllerId)
			{
				return;
			}
		}

		new (&m_Controllers[m_ConnectedControllers]) Controller(controllerId);
		++m_ConnectedControllers;
	}

	Controller::InputInfo InputManager::GetPlayerInputInfo(unsigned int player, const char* controlString) const
	{
		if (player < 0 || player >= m_ConnectedControllers)
		{
			Controller::InputInfo inputInfo;
			inputInfo.State = ControlsMap::ButtonState::None;
			inputInfo.AxisPosition = 0.0f;
			return inputInfo;
		}

		return m_Controllers[player].GetInputInfo(controlString);
	}

	Controller::InputInfo InputManager::GetControllerInputInfo(int controller, const char* controlString) const
	{
		for (unsigned int i = 0; i < m_ConnectedControllers; ++i)
		{
			if (m_Controllers[i].GetControllerId() == controller)
			{
				return m_Controllers[i].GetInputInfo(controlString);
			}
		}

		Controller::InputInfo inputInfo;
		inputInfo.State = ControlsMap::ButtonState::None;
		inputInfo.AxisPosition = 0.0f;
		return inputInfo;
	}

	unsigned int InputManager::GetConnectedControllers() const
	{
		return m_ConnectedControllers;
	}

	unsigned int InputManager::GetMaxControllers() const
	{
		return m_MaxControllers;
	}
}