#include "CommandQueue.h"

#include <cstring>
#include <new>

#include <Memory/MemoryManager.h>

namespace Soul
{
	CommandQueue::Message::Message(const char* string, Payload data) :
		String(string),
		Data(data)
	{

	}

	CommandQueue::CommandQueue(unsigned int capacity) :
		m_Capacity(capacity),
		m_Commands(PartitionArray(Message, capacity)),
		m_Count(0),
		m_NextMessage(0),
		m_NextEmpty(0)
	{

	}

	void CommandQueue::QueueMessage(const char* string, Payload data)
	{
		if (m_Count < m_Capacity)
		{
			new (&m_Commands[m_NextEmpty]) Message(string, data);
			++m_Count;
			m_NextEmpty = (++m_NextEmpty % m_Capacity);
		}
	}

	bool CommandQueue::CheckMessage(const char* string)
	{
		return m_Count > 0 && strcmp(m_Commands[m_NextMessage].String, string) == 0;
	}

	CommandQueue::Message& CommandQueue::ConsumeMessage()
	{
		Message& message = m_Commands[m_NextMessage];
		m_NextMessage = (++m_NextMessage % m_Capacity);
		return message;
	}
}