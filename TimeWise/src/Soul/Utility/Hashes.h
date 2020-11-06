#pragma once

#include <Strings/String.h>

namespace Soul
{
	/*
	Uses the Polynomial Rolling Hash function
	(https://cp-algorithms.com/string/string-hashing.html) to convert a String object into
	a hash.
	*/
	unsigned long long Hash(const String& string);

	/*
	Uses the Polynomial Rolling Hash function
	(https://cp-algorithms.com/string/string-hashing.html) to convert a String object into
	a hash.
	*/
	unsigned long long Hash(const char* string);

	/*
	Hashes integer by simply converting to an unsigned long long.
	*/
	unsigned long long Hash(unsigned int integer);
}