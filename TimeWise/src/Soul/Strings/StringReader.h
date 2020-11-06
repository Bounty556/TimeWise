#pragma once

#include <Strings/String.h>

namespace Soul
{
	/*
	Helper class that aids in reading CString and Soul::Strings line by line. This works quite
	differently from a typical StringStream. First, one of the get functions is called, which 
	stores the resulting string into a variable within this StringReader. This string can then
	be accessed at anytime via GetLastValue().
	Ex:

	String string(...);
	StringReader stringReader(string);

	while (!stringReader.IsAtEnd())
	{
		stringReader.GetNextLine();
		SoulLogInfo("%s", stringReader.GetLastValue());
	}
	*/
	class StringReader
	{
	public:
		StringReader(const String& string);

		/*
		Sets the last string value to be all characters in this string until a \n is reached.
		Does not include the \n in the read string.
		*/
		void GetNextLine();
		
		/*
		Sets the last string value to be the next character in the string.
		*/
		void GetNextChar();
		
		/*
		Sets the last string value to be all characters in this string until the provided
		character is reached. Does not include the character reached, but does set the current
		index to be after the reached character.
		*/
		void GetUntil(char toFind);
		
		/*
		Sets the last string value to be all characters in this string until the provided
		character is reached. Includes the character reached.
		*/
		void GetIncluding(char toFind);
		
		/*
		Sets the last string value to be the rest of the string.
		*/
		void GetRest();

		/*
		Returns the last value read by this StringReader.
		*/
		const char* GetLastValue() const;

		/*
		Returns the underlying Soul::String used by this StringReader for temp strings.
		*/
		const String& GetString() const;

		/*
		Returns whether the entire string has been traversed yet.
		*/
		bool IsAtEnd() const;

	private:
		/*
		The value we last read by this StringReader.
		*/
		String m_LastValue;

		/*
		The start of the string this StringReader is reading.
		*/
		const char* m_StringStart;

		/*
		The current index of the string this StringReader is at.
		*/
		unsigned int m_CurrentIndex;

		/*
		The last index this StringReader is allowed to reach.
		*/
		unsigned int m_LastIndex;
	};
}