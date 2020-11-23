#pragma once

#include <SFML/System/Vector2.hpp>

#include <Strings/String.h>

// TODO: Look into turning these into constexpr functions

namespace Soul
{
	/*
	Contains various math utility functions.
	*/
	namespace Math
	{
		/*
		Computes the value of value^power.
		*/
		int PowInt(int value, unsigned int power);

		/*
		Computes the value of value^power.
		*/
		float PowFloat(float value, int power);

		/*
		Finds the nearest prime that is >= to the provided number.
		*/
		unsigned int FindNextPrime(unsigned int number);

		/*
		Checks to see if this number is prime.
		*/
		bool IsPrime(unsigned int number);

		/*
		Returns the absolute value of this number.
		*/
		float Abs(float number);

		/*
		Rounds the provided float to the nearest integer.
		*/
		int Round(float number);

		/*
		Calculates fast square root of number.
		From: https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
		*/
		float Sqrt(float number);

		/*
		Calculates the normal of the provided vertices. This will always be
		a "left" normal.
		*/
		sf::Vector2f CalculateNormal(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2);

		/*
		Calculates the vector perpendicular to the given vector. This will
		always point "left" of the given vector.
		*/
		sf::Vector2f Perpendicular(const sf::Vector2f& vector);

		/*
		Calculates the projection of the point onto the provided line.
		*/
		sf::Vector2f Project(const sf::Vector2f& point, const sf::Vector2f& line);

		/*
		Calculates the direction from the point to the nearest point on the
		line.
		*/
		sf::Vector2f Reject(const sf::Vector2f& point, const sf::Vector2f& line);

		/*
		Returns the unit vector of the provided vector.
		*/
		sf::Vector2f Normalize(const sf::Vector2f& vector);

		/*
		Calculates the magnitude of the provided vector.
		*/
		float Magnitude(const sf::Vector2f& vector);

		/*
		Calculates the dot product of the provided vectors.
		*/
		float Dot(const sf::Vector2f& a, const sf::Vector2f& b);

		/*
		Returns the max of the two values.
		*/
		float Max(float a, float b);

		/*
		Returns the min of the two values.
		*/
		float Min(float a, float b);

		/*
		Finds the smallest needed vector to move a point out of a polygon.
		*/
		sf::Vector2f CorrectionVector(const sf::Vector2f& point, sf::Vector2f* polygon, unsigned int vertexCount);
	}
}