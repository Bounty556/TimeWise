#pragma once

#include <Files/ControlsFile.h>
#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

namespace Soul
{
	class ControlsFileTests
	{
	public:
		static void RunAllTests()
		{
			RunTest(BasicUse);
			RunTest(LoadingAndWritingFiles);
		}

	private:
		static void BasicUse()
		{
			ControlsFile controlsFile("res/test.controls");

			Assert(controlsFile.GetInputValue("Jump", 'k') == 12);
			Assert(controlsFile.GetInputValue("Jump", 'm') == -1);
			Assert(controlsFile.GetInputValue("Jump", 'a') == -1);
			Assert(controlsFile.GetInputValue("Jump", 'c') == 2);
			Assert(controlsFile.GetInputValue("Shoot", 'a') == 3);
			Assert(controlsFile.GetInputValue("Shoot", 'k') == -1);
			Assert(controlsFile.GetInputValue("Shoot", 'c') == -1);
			Assert(controlsFile.GetInputValue("Shoot", 'm') == 1);
		}

		static void LoadingAndWritingFiles()
		{
			ControlsFile controlsFile("res/test2.controls");

			ControlsMap::Input input;
			int previousValue = controlsFile.GetInputValue("Shoot", 'c');
			input.ControllerButton = previousValue + 1;

			controlsFile.UpdateControls("Shoot", input);
			Assert(controlsFile.GetInputValue("Shoot", 'c') == previousValue + 1);

			controlsFile.WriteToFile();

			ControlsFile controlsFile2("res/test2.controls");

			Assert(controlsFile.GetInputValue("Shoot", 'c') == previousValue + 1);
		}
	};
}