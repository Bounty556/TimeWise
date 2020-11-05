#pragma once

#include <Utility/String.h>

namespace Soul
{
	/*
	A file that uses a Soul::String as it's underlying buffer. Solely to be used for text files.
	*/
	class TextFile
	{
	public:
		TextFile(const char* fileName);
		~TextFile();

		/*
		Writes the contents of the underlying String to the same file that was read.
		*/
		void WriteStringToFile();

		/*
		A shortcut function to get the CString that the Soul::String holds.
		*/
		const char* GetCString() const;

		/*
		Gets the underlying Soul::String that acts as the buffer for this file reader.
		*/
		String& GetString() const;

	private:
		const char* m_FilePath;
		String* m_FileContents;
	};
}