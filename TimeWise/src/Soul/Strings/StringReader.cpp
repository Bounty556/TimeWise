#include "StringReader.h"

#include <string>

namespace Soul
{
	StringReader::StringReader(const String& string) :
		m_LastValue(""),
		m_StringStart(string.GetCString()),
		m_CurrentIndex(0),
		m_LastIndex(string.Length())
	{

	}

	void StringReader::GetNextLine()
	{
		// Windows uses \r\n to signify the enter key, Linux and Unix only use \n. 
		GetUntil('\n');
	}

	void StringReader::GetNextChar()
	{
		m_LastValue = "";
		while (m_CurrentIndex < m_LastIndex)
		{
			if (m_StringStart[m_CurrentIndex] != '\r')
			{
				m_LastValue = m_StringStart[m_CurrentIndex];
				++m_CurrentIndex;
				return;
			}
			++m_CurrentIndex;
		}
	}

	void StringReader::GetUntil(char toFind)
	{
		m_LastValue = "";

		while (m_StringStart[m_CurrentIndex] != toFind && m_CurrentIndex != m_LastIndex)
		{
			if (m_StringStart[m_CurrentIndex] != '\r')
			{
				m_LastValue += m_StringStart[m_CurrentIndex];
			}
			m_CurrentIndex++;
		}

		if (m_CurrentIndex < m_LastIndex)
		{
			// Skip over the character we want to stop at
			m_CurrentIndex++;
		}
	}

	void StringReader::GetIncluding(char toFind)
	{
		m_LastValue = "";

		while (m_StringStart[m_CurrentIndex] != toFind && m_CurrentIndex < m_LastIndex)
		{
			if (m_StringStart[m_CurrentIndex] != '\r')
			{
				m_LastValue += m_StringStart[m_CurrentIndex];
			}
			m_CurrentIndex++;
		}

		if (m_CurrentIndex < m_LastIndex)
		{
			// Add the character we wanted to stop at
			m_LastValue += m_StringStart[m_CurrentIndex];
			m_CurrentIndex++;
		}
	}

	void StringReader::GetRest()
	{
		m_LastValue = "";

		while (m_CurrentIndex < m_LastIndex)
		{
			if (m_StringStart[m_CurrentIndex] != '\r')
			{
				m_LastValue += m_StringStart[m_CurrentIndex];
			}
			m_CurrentIndex++;
		}
	}

	const char* StringReader::GetLastValue() const
	{
		return m_LastValue.GetCString();
	}

	const String& StringReader::GetString() const
	{
		return m_LastValue;
	}

	bool StringReader::IsAtEnd() const
	{
		return m_CurrentIndex == m_LastIndex;
	}
}