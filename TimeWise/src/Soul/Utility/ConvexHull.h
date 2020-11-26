#pragma once

#include <SFML/System/Vector2.hpp>

#include <Memory/UniquePointer.h>
#include <Structures/Set.h>

namespace Soul
{
	class ConvexHull
	{
	public:
		ConvexHull(const Set<sf::Vector2f>& vertices);
		ConvexHull(ConvexHull&&) = delete;
		ConvexHull(const ConvexHull&) = delete;

		const sf::Vector2f& operator[](unsigned int index);

		unsigned int Length() const;

	private:
		/*
		Generates a hull from the provided set of points using the quickhull
		algorithm.
		*/
		void GenerateHull(const Set<sf::Vector2f>& vertices);
		
	private:
		UniquePointer<sf::Vector2f> m_Vertices;
		unsigned int m_Length;
	};
}