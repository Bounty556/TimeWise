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

		float Sqrt(float x)
		{
			unsigned int i = *(unsigned int*)&x;
			// adjust bias
			i += 127 << 23;
			// approximation of square root
			i >>= 1;
			return *(float*)&i;
		}

		sf::Vector2f CalculateNormal(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2)
		{
			sf::Vector2f diff(vertex1 - vertex2);
			float mag = Sqrt(diff.x * diff.x + diff.y * diff.y);
			if (mag == 0)
			{
				return sf::Vector2f(0, 0);
			}

			return sf::Vector2f(-diff.y, diff.x) / mag;
		}

		sf::Vector2f Perpendicular(const sf::Vector2f& vector)
		{
			return sf::Vector2f(-vector.y, vector.x);
		}

		sf::Vector2f Reject(const sf::Vector2f& point, const sf::Vector2f& line)
		{
			return point - (line * (Dot(point, line) / Dot(line, line)));
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

		/*
		TODO: Potential optimizations
		-Send a precomputed center
		-Don't check for collisions if the point is not closer than the furthest vertex from the center
		*/
		bool IsPointInPolygon(const sf::Vector2f& point, sf::Vector2f* polygon, unsigned int vertexCount, const sf::Vector2f& center)
		{
			for (unsigned int i = 0; i < vertexCount; ++i)
			{
				sf::Vector2f pointToSegment = polygon[i] - point;
				sf::Vector2f centerToSegment = polygon[i] - center;
				sf::Vector2f perpSegment = Perpendicular(polygon[(i + 1) % vertexCount] - polygon[i]);

				float a = Dot(pointToSegment, perpSegment);
				float b = Dot(centerToSegment, perpSegment);

				if ((a > 0 && b < 0) || (a < 0 && b > 0))
				{
					return false;
				}
			}

			return true;
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