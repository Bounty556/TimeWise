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
		// TODO: Implement
	}

	int ControlsFile::GetInputValue(const char* controlName, char inputOrigin) const
	{
		String controlString(controlName);
		String inputString(inputOrigin);

		return *(m_Controls.Get(controlString)->Get(inputString));
	}

	void ControlsFile::WriteMapToFile()
	{
		// TODO: Implement
	}

	void ControlsFile::ReadToMap()
	{
		StringReader stringReader(m_File.GetString());

		while (!stringReader.IsAtEnd())
		{
			// The first line should be the name of the control
			stringReader.GetNextLine();
			String controlName(stringReader.GetLastValue());

			Map<String, int> inputValues;

			for (unsigned int i = 0; i < 4; ++i)
			{
				// Get the first input type and value
				stringReader.GetNextChar();
				String inputOrigin(stringReader.GetLastValue());

				stringReader.GetNextChar();
				stringReader.GetNextLine();

				inputValues.AddPair(inputOrigin, (int)(stringReader.GetString().ToInt()));
			}

			m_Controls.AddPair(controlName, std::move(inputValues));
		}
	}
}