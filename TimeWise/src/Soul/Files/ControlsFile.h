#pragma once

#include <Files/TextFile.h>
#include <Input/ControlsMap.h>
#include <Utility/Map.h>
#include <Utility/Vector.h>

namespace Soul
{
	class ControlsFile
	{
	public:
		ControlsFile(const char* fileName);

		void UpdateControls(const ControlsMap::Input& input);

	private:
		void WriteToFile();

	private:
		/*
		The opened .controls file.
		*/
		TextFile m_File;


	};
}