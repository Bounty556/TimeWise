#pragma once

#include <Files/TextFile.h>
#include <Input/ControlsMap.h>
#include <Utility/Map.h>
#include <Strings/String.h>

namespace Soul
{
	class ControlsFile
	{
	public:
		ControlsFile(const char* fileName);

		/*
		Updates this controls file to contain the information contained in the provided input
		mapping.
		*/
		void UpdateControls(const ControlsMap::Input& input);

	private:
		/*
		Writes the contents of the m_Controls nested map to the .controls file.
		*/
		void WriteToFile();

		/*
		Reads the file into the m_Controls nested map.
		*/

	private:
		/*
		The opened .controls file.
		*/
		TextFile m_File;

		/*
		A representation of the .controls file as a nested map.
		*/
		Map<Map<String>> m_Controls;
	};
}