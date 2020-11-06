#pragma once

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
	}
}