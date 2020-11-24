#pragma once

#include <SFML/System/Vector2.hpp>
#include <Structures/Set.h>

namespace Soul
{
	class Simplex
	{
	public:
		Simplex();

		void AddVertex(sf::Vector2f vertex);

		bool DoGJK(sf::Vector2f& direction);

		void FindClosestEdge(sf::Vector2f& edgeNormal, float& edgeDistance, const sf::Vector2f& point) const;

	private:
		Set<sf::Vector2f> m_Vertices;
	};
}