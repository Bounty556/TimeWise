#include "String.h"

#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>

#include <cstring>

namespace Soul
{
	String::String(const char* initialString) :
		m_StringLength(strlen(initialString))
	{
		if (m_StringLength + 1 > 32)
		{
			// Determine capacity through doubling highest bit
			unsigned int bits = m_StringLength + 1;
			unsigned int halfCount = 0;
			while (bits > 0)
			{
				bits /= 2;
				halfCount++;
			}

			m_StringCapacity = 1 << halfCount;
		}
		else
		{
			m_StringCapacity = 64; // The minimum is 64 bytes
		}

		m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

		memcpy(m_CString, initialString, m_StringLength + 1);
	}

	String::String(const String& otherString) :
		m_StringLength(otherString.m_StringLength),
		m_StringCapacity(otherString.m_StringCapacity)
	{
		SoulLogInfo("Copy constructor called");

		m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

		memcpy(m_CString, otherString.GetCString(), m_StringLength + 1);
	}

	String::String(String&& otherString) :
		m_StringLength(otherString.m_StringLength),
		m_StringCapacity(otherString.m_StringCapacity)
	{
		SoulLogInfo("Move constructor called");

		m_CString = otherString.m_CString;
		otherString.m_CString = nullptr;
	}

	String::~String()
	{
		MemoryManager::FreeMemory(m_CString);
	}

	String& String::operator=(const String& otherString)
	{
		m_StringLength = otherString.m_StringLength;
		m_StringCapacity = otherString.m_StringCapacity;
		
		MemoryManager::FreeMemory(m_CString);

		m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

		memcpy(m_CString, otherString.m_CString, m_StringLength + 1);

		return *this;
	}

	String& String::operator+=(const String& otherString)
	{
		return operator+=(otherString.m_CString);
	}

	String& String::operator+=(const char* otherString)
	{
		unsigned int otherLength = strlen(otherString);
		unsigned int tempLength = m_StringLength + otherLength;
		while (m_StringCapacity <= tempLength)
		{
			m_StringCapacity *= 2;
		}

		char* tempPointer = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

		// Put the values of both the strings at the temp pointer
		unsigned int stringIndex = 0;
		for (unsigned int i = 0; i < m_StringLength; ++i)
		{
			tempPointer[stringIndex] = m_CString[i];
			++stringIndex;
		}

		// Add 1 to get the null terminator
		for (unsigned int i = 0; i < otherLength + 1; ++i)
		{
			tempPointer[stringIndex] = otherString[i];
			++stringIndex;
		}

		// Clean up and reassign
		MemoryManager::FreeMemory(m_CString);
		m_StringLength = tempLength;
		m_CString = tempPointer;

		return *this;
	}

	const char String::operator[](unsigned int index) const
	{
		if (index < 0 || index >= m_StringLength)
		{
			Assert(false);
			SoulLogError("Invalid string index");
		}

		return m_CString[index];
	}

	unsigned int String::Length() const
	{
		return m_StringLength;
	}

	int String::CompareTo(const String& otherString) const
	{
		return strcmp(m_CString, otherString.m_CString);
	}

	const char* String::GetCString() const
	{
		return m_CString;
	}
}