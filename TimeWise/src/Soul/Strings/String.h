#pragma once

namespace Soul
{
	/*
	This is to be used in place of the C Standard Template Library strings. They should behave
	almost identically, but instead use our built-in memory arena. Thus for these to work, the
	MemoryManager class must have been initialized with Allocate().
	*/
	class String
	{
	public:
		String(const char* initialString = "");
		String(const char initialChar);
		String(unsigned int capacity);

		String(const String& otherString); // Copy constructor
		String(String&& otherString); // Move constructor
		
		~String();
		
		String& operator=(const String& otherString); // Copy assignment
		String& operator=(const char* otherString);
		String& operator=(const char otherChar);

		String& operator+=(const String& otherString);
		String& operator+=(const char* otherString);
		String& operator+=(const char otherChar);

		bool operator==(const String& otherString) const;
		bool operator==(const char* otherString) const;

		bool operator!=(const String& otherString) const;
		bool operator!=(const char* otherString) const;

		const char operator[](unsigned int index) const;

		/*
		Returns the length of the string. Does not include the null terminator.
		*/
		unsigned int Length() const;

		/*
		Sets the length of this string. Should only be used if directly editing the buffer
		itself, such as when loading file contents into the string.
		*/
		void SetLength(unsigned int length);

		/*
		Returns:
		< 0 if this string is lexicographically less than the provided string.
		0 if this string is lexicographically equivalent to the provided string.
		> 0 if this string is lexicographically larger than the provided string.
		*/
		int CompareTo(const String& otherString) const;

		/*
		Returns:
		< 0 if this string is lexicographically less than the provided string.
		0 if this string is lexicographically equivalent to the provided string.
		> 0 if this string is lexicographically larger than the provided string.
		*/
		int CompareTo(const char* otherString) const;

		/*
		Returns the C-Style string underlying this String object.
		*/
		const char* GetCString() const;

		/*
		Returns the address of the start of the buffer in the MemoryArena that holds the string.
		USE WITH CAUTION!!!
		*/
		char* GetBufferStart() const;

		/*
		Attempts to convert the contents of this String into an integer. Will return -1 if no
		integer is found.
		*/
		int ToInt() const;

	private:
		char* m_CString;

		/*
		Length of the number of characters this string has.
		*/
		unsigned int m_StringLength;

		/*
		Number of characters that this string could potentially have before it needs to request
		more memory.
		*/
		unsigned int m_StringCapacity;

		/*
		The smallest capacity we would partition.
		*/
		const unsigned int m_MinimumCapacity = 32;
	};
}