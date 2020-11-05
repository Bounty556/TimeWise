#include "String.h"

#include <Memory/MemoryManager.h>
#include <Utility/Macros.h>
#include <Utility/Math.h>

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
		m_CString = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

		memcpy(m_CString, otherString.GetCString(), m_StringLength + 1);
	}

	String::String(String&& otherString) :
		m_StringLength(otherString.m_StringLength),
		m_StringCapacity(otherString.m_StringCapacity)
	{
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

		// There are 2 scenarios here: one where we don't exceed our current string capacity,
		// and one where we do. If we exceed our string capacity, we need to repartition memory
		// for our string and move things over
		bool isOverCapacity = false;

		while (m_StringCapacity <= tempLength + 1)
		{
			m_StringCapacity *= 2;
			isOverCapacity = true;
		}

		if (isOverCapacity)
		{
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
		}
		else
		{
			// Add the other strings characters to the end of our string
			for (unsigned int i = 0; i < otherLength + 1; ++i)
			{
				m_CString[m_StringLength + i] = otherString[i];
			}

			m_StringLength = tempLength;
		}

		return *this;
	}

	String& String::operator+=(const char otherChar)
	{
		
		// There are 2 scenarios here: one where we don't exceed our current string capacity,
		// and one where we do. If we exceed our string capacity, we need to repartition memory
		// for our string and move things over
		bool isOverCapacity = false;
		if (m_StringCapacity <= m_StringLength + 2)
		{
			m_StringCapacity *= 2;
			isOverCapacity = true;
		}

		if (isOverCapacity)
		{
			char* tempPointer = (char*)MemoryManager::PartitionMemory(m_StringCapacity);

			// Put the values of both the strings at the temp pointer
			unsigned int stringIndex = 0;
			for (unsigned int i = 0; i < m_StringLength; ++i)
			{
				tempPointer[stringIndex] = m_CString[i];
				++stringIndex;
			}
			
			tempPointer[stringIndex] = otherChar;
			tempPointer[stringIndex + 1] = '\n';

			// Clean up and reassign
			MemoryManager::FreeMemory(m_CString);
			m_CString = tempPointer;
		}
		else
		{
			m_CString[m_StringLength] = otherChar;
			m_CString[m_StringLength + 1] = '\n';
		}
		
		if (otherChar != '\0')
		{
			m_StringLength += 1;
		}

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

	int String::CompareTo(const char* otherString) const
	{
		return strcmp(m_CString, otherString);
	}

	const char* String::GetCString() const
	{
		return m_CString;
	}

	int String::ToInt() const
	{
		// Extract only the number
		String number;
		bool encounteredNumber = false;
		bool isNegative = false;
		for (unsigned int i = 0; i < m_StringLength; ++i)
		{
			// If this is a numerical character
			if (m_CString[i] >= 48 && m_CString[i] <= 57)
			{
				// Check to see if this is negative
				if (encounteredNumber == false && i > 0 && m_CString[i - 1] == '-')
				{
					isNegative = true;
				}
				encounteredNumber = true;
				number += m_CString[i];
			}
			else if (!encounteredNumber && m_CString[i] == '.')
			{
				encounteredNumber = true;
				number += '0';
				break;
			}
			else if (encounteredNumber)
			{
				break;
			}
		}

		if (encounteredNumber)
		{
			int convertedInt = 0;

			for (unsigned int i = 0; i < number.Length(); ++i)
			{
				int charValue = number[i] - 48;
				convertedInt += charValue * Math::Pow(10, number.Length() - (i + 1));
			}

			if (isNegative)
			{
				convertedInt *= -1;
			}

			return convertedInt;
		}

		return -1;
	}

	float String::ToFloat() const
	{
		return -1.0f;
	}
}