#pragma once

#include <Strings/String.h>

namespace Soul
{
	/*
	A file that uses a Soul::String as it's underlying buffer. Solely to be used for text files.

	The file is automatically read from when the object is created, and te underlying
	Soul::String object can be written and read from whenever desired. When you want to write
	back to the file, simply call WriteStringToFile(), and whatever is in the Soul::String will
	overwrite the contents of the file.
	*/
	class TextFile
	{
	public:
		TextFile(const char* fileName);
		TextFile() = delete;
		
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