#pragma once

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Structures/Queue.h>
#include <Utility/Macros.h>

namespace Soul
{
	class QueueTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(BasicUse);
			RunTest(RollBuffer);
		}

	private:
		static void BasicUse()
		{
			Queue<int> queue(14);

			for (int i = 0; i < 13; ++i)
			{
				queue.Enqueue(i);
			}

			for (int i = 0; i < 13; ++i)
			{
				Assert(queue.Dequeue() == i);
			}
		}

		static void RollBuffer()
		{
			Queue<int> queue(5);

			for (int i = 0; i < 5; ++i)
			{
				for (int i = 0; i < 5; ++i)
				{
					queue.Enqueue(i);
				}

				for (int i = 0; i < 5; ++i)
				{
					Assert(queue.Dequeue() == i);
				}
			}
		}
	};
}