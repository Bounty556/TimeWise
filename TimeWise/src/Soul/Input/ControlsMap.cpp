#include "ControlsMap.h"

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	ControlsMap::ControlsMap(const char* inputString, unsigned int inputs) :
		m_ControlsCount(inputs)
	{
		m_Controls = (Input*)MemoryManager::PartitionMemory(m_ControlsCount * sizeof(Input));

		// Put all of the inputs into the array, initialize values
		for (unsigned int character = 0, i = 0; i < m_ControlsCount; ++i)
		{
			m_Controls[i] = {};
			// TODO: Implement using custom string
			//strcpy(m_Controls[i].InputName, "");
			m_Controls[i].State = ButtonState::None;
			while (inputString[character] != ',' && inputString[character] != ';')
			{
				// TODO: Implement using custom string
				//strcat(m_Controls[i].InputName, inputString[character]);
				++character;
			}

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

	const ControlsMap::Input& ControlsMap::GetInputInfo(const char* inputName) const
	{
		for (unsigned int i = 0; i < m_ControlsCount; i++)
		{
			if (strcmp(inputName, m_Controls[i].InputName))
			{
				return m_Controls[i];
			}
		}

		SoulLogError("Unable to find control mapping for input %s", inputName);
		Assert(false);
		return m_Controls[0];
	}

	void ControlsMap::SetControllerInput(const char* input, unsigned int controllerButton)
	{

	}

	void ControlsMap::SetMouseInput(const char* input, sf::Mouse::Button mouseButton)
	{

	}

	void ControlsMap::SetKeyboardInput(const char* input, sf::Keyboard::Key keyboardKey)
	{

	}
}