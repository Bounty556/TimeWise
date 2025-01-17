#pragma once

#include <Files/TextFile.h>
#include <Input/ControlsMap.h>
#include <Structures/Map.h>
#include <Strings/String.h>

namespace Soul
{
	/*
	The .controls file format is as follows:

	<Name of the control>
	<Input specifier> <Input id>
	<Input specifier> <Input id>
	<Input specifier> <Input id>
	<Input specifier> <Input id>
	<Name of the control>
	<Input specifier> <Input id>
	<Input specifier> <Input id>
		        .
		        .
		        .

	Where:
	<Name of the control> is the name of the action you'd like to happen for the given
	control, e.g "Jump".
	<Input specifier> is k, m, c, a, for Keyboard, Mouse, Controller Button and Controller Axis respectively.
	<Input id> either an integer, or -1 for none

	Example .controls file:

	Jump
	k 12
	m -1
	a -1
	c 2
	Shoot
	a 3
	k -1
	c -1
	m 1
	*/
	class ControlsFile
	{
	public:
		ControlsFile() = delete;
		ControlsFile(const char* fileName);
		ControlsFile(ControlsFile&& otherFile); // Move constructor

		/*
		Updates this controls file to contain the information contained in the provided input
		mapping.
		*/
		void UpdateControls(const char* controlName, const ControlsMap::Input& input);

		/*
		Returns the current input value loaded from the .controls from for the given control.
		*/
		int GetInputValue(const char* controlName, char inputOrigin) const;

		/*
		Writes the contents of the m_Controls nested map to the .controls file.
		*/
		void WriteToFile();

		/*
		Returns a list of all of the names of the inputs that were loaded.
		*/
		Vector<String*> GetInputNames() const;

	private:
		/*
		Reads the file into the m_Controls nested map.
		*/
		void ReadToMap();

	private:
		/*
		The opened .controls file.
		*/
		TextFile m_File;

		/*
		A representation of the .controls file as a nested map.
		*/
		Map<String, Map<String, int>> m_Controls;
	};
}