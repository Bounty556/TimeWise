#include "Hashes.h"

#include <string>

namespace Soul
{
	unsigned long long hashPowers[] = {1,53,2809,148877,7890481,418195493,22164361129,1174711139837,62259690411361,3299763591802133,174887470365513060,9269035929372193000};

	unsigned long long Hash(const String& string)
	{
		unsigned int power = 0;
		unsigned long long hashValue = 0;
		unsigned long long m = 1000000009;

		for (unsigned int i = 0; i < string.Length(); ++i)
		{
			hashValue += (string[i] * hashPowers[power]) % m;

			power = (power + 1) % 12;
		}

		return hashValue;
	}

	unsigned long long Hash(const char* string)
	{
		unsigned int power = 0;
		unsigned long long hashValue = 0;
		unsigned long long m = 1000000009;
		unsigned int stringLength = strlen(string);

		for (unsigned int i = 0; i < stringLength; ++i)
		{
			hashValue += (string[i] * hashPowers[power]) % m;

			power = (power + 1) % 12;
		}

		if (hashValue == 0)
		{
			hashValue = 1;
		}

		return hashValue;
	}

	unsigned long long Hash(unsigned integer)
	{
		return (unsigned long long)integer;
	}
}