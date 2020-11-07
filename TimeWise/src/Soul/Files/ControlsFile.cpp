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

	ControlsFile::ControlsFile(ControlsFile&& otherFile) :
		m_File(std::move(otherFile.m_File)),
		m_Controls(std::move(otherFile.m_Controls))
	{

	}

	void ControlsFile::UpdateControls(const char* controlName, const ControlsMap::Input& input)
	{
		Map<String, int>& inputMap = *(m_Controls.Get(controlName));
		*(inputMap.Get('k')) = input.KeyboardKey;
		*(inputMap.Get('m')) = input.MouseButton;
		*(inputMap.Get('a')) = input.Axis;
		*(inputMap.Get('c')) = input.ControllerButton;
	}

	int ControlsFile::GetInputValue(const char* controlName, char inputOrigin) const
	{
		String controlString(controlName);
		String inputString(inputOrigin);

		return *(m_Controls.Get(controlString)->Get(inputString));
	}

	void ControlsFile::WriteToFile()
	{
		String& fileString = m_File.GetString();
		fileString = "";
		
		Vector<String*> keys = m_Controls.GetKeys();
		for (unsigned int i = 0; i < keys.Length(); i++)
		{
			Map<String, int>& inputMap = *(m_Controls.Get(*keys[i]));

			fileString += keys[i]->GetCString();
			fileString += "\nk ";
			fileString += String::IntToString(*inputMap.Get(String('k')));
			fileString += "\nm ";
			fileString += String::IntToString(*inputMap.Get(String('m')));
			fileString += "\na ";
			fileString += String::IntToString(*inputMap.Get(String('a')));
			fileString += "\nc ";
			fileString += String::IntToString(*inputMap.Get(String('c')));
			if (i != keys.Length() - 1)
			{
				fileString += '\n';
			}
		}

		m_File.WriteStringToFile();
	}

	Vector<String*> ControlsFile::GetInputNames() const
	{
		return m_Controls.GetKeys();
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