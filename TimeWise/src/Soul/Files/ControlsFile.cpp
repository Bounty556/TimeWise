#include "ControlsFile.h"

#include <Strings/StringReader.h>
#include <Utility/Math.h>

namespace Soul
{
	ControlsFile::ControlsFile(const char* fileName) :
		m_File(fileName),
		m_Controls()
	{
		ReadToMap();
	}

	void ControlsFile::UpdateControls(const ControlsMap::Input& input)
	{

	}

	int ControlsFile::GetInputValue(const char* controlName, char inputOrigin) const
	{
		return 0;
	}

	void ControlsFile::WriteMapToFile()
	{

	}

	void ControlsFile::ReadToMap()
	{
		//m_Controls.Clear();

		//StringReader stringReader(m_File.GetString());

		//while (!stringReader.IsAtEnd())
		//{

		//	// The first line should be the name of the control
		//	stringReader.GetNextLine();
		//	unsigned long long controlNameHash = Math::HashString(stringReader.GetLastValue());

		//	Map<int> inputValues;

		//	for (unsigned int i = 0; i < 4; ++i)
		//	{
		//		// Get the first input type and value
		//		stringReader.GetNextChar();
		//		unsigned long long hash = Math::HashString(stringReader.GetLastValue());

		//		stringReader.GetNextChar();
		//		stringReader.GetNextLine();

		//		inputValues.AddPair(hash, stringReader.GetString().ToInt());
		//	}

		//	m_Controls.AddPair(controlNameHash, std::move(inputValues));
		//}
	}
}