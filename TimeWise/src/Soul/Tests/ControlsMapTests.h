#pragma once

#include <Input/ControlsMap.h>
#include <Logging/Logger.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	class ControlsMapTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(BasicUse);
		}

	private:
		static void BasicUse()
		{
			ControlsMap controlsMap;
			ControlsMap::Input testInput1;
			ControlsMap::Input testInput2;

			testInput1.KeyboardKey = sf::Keyboard::Space;

			controlsMap.AddInput("Jump", testInput1);
			controlsMap.AddInput("Shoot", testInput2);

			controlsMap.SetControllerAxis("Shoot", sf::Joystick::Y);

			Assert(controlsMap.GetInputInfo("Jump").KeyboardKey == sf::Keyboard::Space);
			Assert(controlsMap.GetInputInfo("Jump").MouseButton == -1);
			Assert(controlsMap.GetInputInfo("Jump").ControllerButton == -1);
			Assert(controlsMap.GetInputInfo("Jump").Axis == -1);
			Assert(controlsMap.GetInputInfo("Shoot").KeyboardKey == -1);
			Assert(controlsMap.GetInputInfo("Shoot").MouseButton == -1);
			Assert(controlsMap.GetInputInfo("Shoot").ControllerButton == -1);
			Assert(controlsMap.GetInputInfo("Shoot").Axis == sf::Joystick::Y);
		}
	};
}