#pragma once

#include <Memory/UniquePointer.h>

namespace Soul
{
	class CommandQueue
	{
	public:
		struct Message
		{
			Message(const char* string, void* data);
			const char* String;
			void* Data;
		};

	public:
		CommandQueue(unsigned int capacity = 32);

		/*
		Queues up a new message in the queue.
		*/
		void QueueMessage(const char* string, void* data);

		/*
		Checks to make sure there is a message available, and matches the given message.
		*/
		bool CheckMessage(const char* string);

		/*
		Returns the oldest message in the queue.
		*/
		Message& ConsumeMessage();

	private:
		unsigned int m_Capacity;

		UniquePointer<Message> m_Commands;

		unsigned int m_Count;

		unsigned int m_NextMessage;

		unsigned int m_NextEmpty;
	};
}