#include "ControlsMap.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	ControlsMap::ControlsMap(const char* inputString, unsigned int inputs)
	{
		m_Controls = (Input*)MemoryManager::PartitionMemory(inputs * sizeof(Input));

		// Put all of the inputs into the array

	}

	ControlsMap::~ControlsMap()
	{
		MemoryManager::FreeMemory(m_Controls);
	}

	const ControlsMap::Input& ControlsMap::GetInputInfo(const char* inputName) const
	{
		return m_Controls[0];
	}
}