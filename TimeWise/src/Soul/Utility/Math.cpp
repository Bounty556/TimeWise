#include "Math.h"

#include <cstring>
#include <new>

namespace Soul
{
	namespace Math
	{
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

		unsigned int FindNextPrime(unsigned int number)
		{
			while (!IsPrime(number))
			{
				number++;
			}

			return number;
		}

		bool IsPrime(unsigned int number)
		{
			// Check to see if even
			if (number % 2 == 0)
			{
				return false;
			}

			unsigned int half = number / 2;

			while (half >= 3)
			{
				if (number % half == 0)
				{
					return false;
				}
				half -= 1;
			}

			return true;
		}

		float Abs(float number)
		{
			if (number < 0.0f)
			{
				return -number;
			}
			return number;
		}

		int Round(float number)
		{
			float num = number - (int)number;

			if (num > 0.5f)
			{
				return (int)(number + 1.0f);
			}
			else
			{
				return (int)(number);
			}
		}
	}
}