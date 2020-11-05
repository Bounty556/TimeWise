#include "Math.h"

namespace Soul
{
	namespace Math
	{
		// TODO: Look into SIMDing this
		int Pow(int value, unsigned int power)
		{
			int total = 1;

			for (int i = 0; i < power; i++)
			{
				total *= value;
			}

			return total;
		}
	}
}