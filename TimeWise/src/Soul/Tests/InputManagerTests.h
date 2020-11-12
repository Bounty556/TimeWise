#pragma once

#include <Input/InputManager.h>
#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	class InputManagerTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(BasicUse);
		}

	private:
		static void BasicUse()
		{
			InputManager input(1);
			input.AddController(-1);

			Assert(input.GetConnectedControllers() == 1);
			Assert(input.GetMaxControllers() == 1);
		}
	};
}