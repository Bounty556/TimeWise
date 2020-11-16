#pragma once

#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>
#include <Other/Logger.h>
#include <Utility/Macros.h>
#include <Strings/String.h>

namespace Soul
{
	class SmartPointerTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(UniquePtr);
		}

	private:
		static void UniquePtr()
		{
			UniquePointer<int> intArray(PartitionArray(int, 50));
		}
	};
}