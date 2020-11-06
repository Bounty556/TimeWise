#pragma once

#include <Files/TextFile.h>
#include <Utility/Map.h>
#include <Utility/Vector.h>

namespace Soul
{
	class ControlsFile
	{
	public:
		ControlsFile(const char* fileName);



	private:
		void WriteToFile();

	private:
		TextFile m_File;
	};
}