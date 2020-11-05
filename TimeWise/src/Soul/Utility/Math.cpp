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

		// TODO: Look into SIMDing this
		float Pow(float value, int power)
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
	}
}