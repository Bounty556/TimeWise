#include "Math.h"

#include <new>

namespace Soul
{
	namespace Math
	{
		unsigned long long hashPowers[] = {1,53,2809,148877,7890481,418195493,22164361129,1174711139837,62259690411361,3299763591802133,174887470365513060,9269035929372193000};

		int PowInt(int value, unsigned int power)
		{
			int total = 1;

			for (unsigned int i = 0; i < power; i++)
			{
				total *= value;
			}

			return total;
		}

		float PowFloat(float value, int power)
		{
			float total = 1.0f;
			bool isNegative = false;

			if (power < 0)
			{
				isNegative = true;
				power = -power;
			}

			for (int i = 0; i < power; i++)
			{
				total *= value;
			}

			if (isNegative)
			{
				total = 1.0f / total;
			}

			return total;
		}

		unsigned long long HashString(const String& string)
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
	}
}