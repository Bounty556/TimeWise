#pragma once

#include <Memory/MemoryManager.h>
#include <Structures/CommandQueue.h>
#include <Utility/Macros.h>

#include <new>

namespace Soul
{
	class CommandQueueTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(BasicUse);
		}

	private:
		static void BasicUse()
		{
			CommandQueue queue;

			queue.QueueMessage("Delete this", Partition(int));

			Assert(queue.CheckMessage("Delete this"));

			MemoryManager::FreeMemory((int*)queue.ConsumeMessage().Data);
		}
	};
}