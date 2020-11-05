#pragma once

#include "TextFile.h"

namespace Soul
{
	/*
	A wrapper for the .controls file format. Contains an easy-to-read-and-edit format that gets
	parsed from the file provided.
	*/
	class ControlFile
	{
	public:
		ControlFile(const char* fileName);

	private:
		TextFile m_ControlFile;
	};
}