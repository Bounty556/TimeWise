#pragma once

#include <Files/TextFile.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	class TextFileTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(BasicUse);
		}

	private:
		static void BasicUse()
		{
			TextFile file("res/test.controls");
		}
	};
}