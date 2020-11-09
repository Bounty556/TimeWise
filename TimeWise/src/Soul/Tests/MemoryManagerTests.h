#pragma once

#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Strings/String.h>
#include <Utility/Macros.h>
#include <Utility/Vector.h>

namespace Soul
{
	class MemoryManagerTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(SimplePlacement);
			RunTest(FreeMemoryPlacement);
		}

	private:
		static void SimplePlacement()
		{
			Vector<String>* stringVector1 = Partition(Vector<String>);
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");

			MemoryManager::FreeMemory(stringVector1);
		}

		static void FreeMemoryPlacement()
		{
			Vector<String>* stringVector1 = Partition(Vector<String>);
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");
			stringVector1->Push("NewString");

			Vector<String>* stringVector2 = Partition(Vector<String>);
			stringVector2->Push("NewString");
			stringVector2->Push("NewString");
			stringVector2->Push("NewString");
			stringVector2->Push("NewString");

			MemoryManager::FreeMemory(stringVector1);

			Vector<String>* stringVector3 = Partition(Vector<String>);
			stringVector3->Push("NewString");
			stringVector3->Push("NewString");
			stringVector3->Push("NewString");
			stringVector3->Push("NewString");

			MemoryManager::FreeMemory(stringVector2);
			MemoryManager::FreeMemory(stringVector3);
		}
	};
}