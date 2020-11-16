#pragma once

#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>
#include <Memory/SharedPointer.h>
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
			RunTest(SharedPtr);
		}

	private:
		static void UniquePtr()
		{
			UniquePointer<int> intArray(PartitionArray(int, 50));

			UniquePointer<int> otherArray(std::move(intArray));

			for (unsigned int i = 0; i < 50; ++i)
			{
				otherArray[i] = 2;
			}

			UniquePointer<int> moveTest(nullptr);

			{
				UniquePointer<int> newArray(PartitionArray(int, 50));
				moveTest = std::move(newArray);
			}

			moveTest[0] = 1;

			moveTest = nullptr;
		}
		
		static void SharedPtr()
		{
			SharedPointer<int> intArray(PartitionArray(int, 50));
			SharedPointer<int> otherArray(std::move(intArray));

			{
				SharedPointer<int> copy(otherArray);
			}

			for (unsigned int i = 0; i < 50; ++i)
			{
				otherArray[i] = 1;
			}
		}
	};
}