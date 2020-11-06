#pragma once

#include <Strings/String.h>

namespace Soul
{
	/*
	Helper class that aids in reading CString and Soul::Strings line by line.
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