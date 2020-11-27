#include "Math.h"

#include <cstring>
#include <new>

#include <Other/Logger.h>

namespace Soul
{
	namespace Math
	{
		void Clamp(float& value, float min, float max)
		{
			value = Min(value, max);
			value = Max(value, min);
		}

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

		float Sqrt(float x)
		{
			unsigned int i = *(unsigned int*)&x;
			// Adjust bias
			i += 127 << 23;
			// Approximation of square root
			i >>= 1;
			return *(float*)&i;
		}

		sf::Vector2f Normal(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2)
		{
			sf::Vector2f diff(vertex1 - vertex2);
			float mag = Magnitude(diff);
			if (mag == 0.0f)
			{
				return sf::Vector2f(0, 0);
			}

			return sf::Vector2f(-diff.y, diff.x) / mag;
		}

		sf::Vector2f Normal(const sf::Vector2f& line)
		{
			float mag = Magnitude(line);
			if (mag == 0.0f)
			{
				return sf::Vector2f(0, 0);
			}

			return sf::Vector2f(-line.y, line.x) / mag;
		}

		sf::Vector2f Perpendicular(const sf::Vector2f& vector)
		{
			return sf::Vector2f(-vector.y, vector.x);
		}

		sf::Vector2f Project(const sf::Vector2f& point, const sf::Vector2f& line)
		{
			float dot = Dot(line, line);

			if (dot == 0.0f)
			{
				return sf::Vector2f(0.0f, 0.0f);
			}

			return line * (Dot(point, line) / dot);
		}

		sf::Vector2f Reject(const sf::Vector2f& point, const sf::Vector2f& line)
		{
			return point - Project(point, line);
		}

		sf::Vector2f Normalize(const sf::Vector2f& vector)
		{
			float mag = Magnitude(vector);
			if (mag == 0.0f)
			{
				return sf::Vector2f(0, 0);
			}
			return vector / mag;
		}

		float Magnitude(const sf::Vector2f& vector)
		{
			 return Sqrt(vector.x * vector.x + vector.y * vector.y);
		}

		float Dot(const sf::Vector2f& a, const sf::Vector2f& b)
		{
			return a.x * b.x + a.y * b.y;
		}

		float Max(float a, float b)
		{
			if (a >= b)
			{
				return a;
			}
			else
			{
				return b;
			}
		}

		float Min(float a, float b)
		{
			if (a <= b)
			{
				return a;
			}
			else
			{
				return b;
			}
		}

		sf::Vector2f CorrectionVector(const sf::Vector2f& point, sf::Vector2f* polygon, unsigned int vertexCount)
		{
			sf::Vector2f smallest;
			float mag = 99999999.0f;

			for (unsigned int i = 0; i < vertexCount; ++i)
			{
				sf::Vector2f segment = polygon[i] - polygon[(i + 1) % vertexCount];
				sf::Vector2f shiftedPoint = point - polygon[(i + 1) % vertexCount];
				sf::Vector2f reject = Reject(shiftedPoint, segment);
				float rejectMagnitude = Magnitude(reject);

				if (rejectMagnitude < mag)
				{
					smallest = -reject;
					mag = rejectMagnitude;
				}
			}

			return smallest;
		}
	}
}