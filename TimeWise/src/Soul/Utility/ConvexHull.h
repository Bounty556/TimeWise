#pragma once

#include <SFML/System/Vector2.hpp>

#include <Memory/UniquePointer.h>

namespace Soul
{
	class ConvexHull
	{
	public:
		ConvexHull(const UniquePointer<sf::Vector2f>& vertices, unsigned int vertexCount);

	private:
		void GenerateHull(const UniquePointer<sf::Vector2f>& vertices, unsigned int vertexCount);
		
	private:
		UniquePointer<sf::Vector2f> m_Vertices;
	};
}