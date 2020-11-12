#include "InputManager.h"

#include <Other/MemoryManager.h>

namespace Soul
{
	InputManager::InputManager(unsigned int maxControllerCount) :
		m_Controllers(PartitionArray(Controller, maxControllerCount)),
		m_MaxControllers(maxControllerCount),
		m_ConnectedControllers(0)
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

	bool InputManager::IsButtonDown(int controller, const char* controlString)
	{
		for (unsigned int i = 0; i < m_ConnectedControllers; ++i)
		{
			if (m_Controllers[i].GetControllerId() == controller)
			{
				return m_Controllers[i].GetInputInfo(controlString).State & ControlsMap::ButtonState::Held;
			}
		}

		return false;
	}

	bool InputManager::WasButtonPressed(int controller, const char* controlString)
	{
		for (unsigned int i = 0; i < m_ConnectedControllers; ++i)
		{
			if (m_Controllers[i].GetControllerId() == controller)
			{
				return m_Controllers[i].GetInputInfo(controlString).State & ControlsMap::ButtonState::Pressed;
			}
		}

		return false;
	}

	bool InputManager::WasButtonReleased(int controller, const char* controlString)
	{
		for (unsigned int i = 0; i < m_ConnectedControllers; ++i)
		{
			if (m_Controllers[i].GetControllerId() == controller)
			{
				return m_Controllers[i].GetInputInfo(controlString).State & ControlsMap::ButtonState::Released;
			}
		}

		return false;
	}

	float InputManager::AxisPosition(int controller, const char* controlString)
	{
		for (unsigned int i = 0; i < m_ConnectedControllers; ++i)
		{
			if (m_Controllers[i].GetControllerId() == controller)
			{
				return m_Controllers[i].GetInputInfo(controlString).AxisPosition;
			}
		}

		return 0.0f;
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