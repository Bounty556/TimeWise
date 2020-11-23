#pragma once

#include <SFML/System/Vector2.hpp>
#include <Memory/UniquePointer.h>

namespace Soul
{
	class Simplex
	{
	public:
		Simplex();

		void AddVertex(sf::Vector2f vertex);

		bool DoGJK(sf::Vector2f& direction);

	private:
		UniquePointer<sf::Vector2f> m_Vertices;
		unsigned int m_VertexCount;
	};
}