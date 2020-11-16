#pragma once

#include <Memory/UniquePointer.h>
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

		TextFile(TextFile&& otherFile); // Move constructor

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
		/*
		The name/path of the file this object has opened.
		*/
		const char* m_FilePath;

		/*
		A pointer to the underlying string that contains the contents of the file this object 
		has opened. A pointer is needed here for optimization, as we want to set the initial
		capacity of the string to be the size of the opened file.
		*/
		UniquePointer<String> m_FileContents;
	};
}