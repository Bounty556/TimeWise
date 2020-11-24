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

		void InsertVertex(unsigned int index, sf::Vector2f vertex);

		bool DoGJK(sf::Vector2f& direction);

		/*
		Finds the edge on this 
		*/
		void FindClosestEdge(sf::Vector2f& outEdgeNormal, float& outEdgeDistance, unsigned int& outEdgeIndex, const sf::Vector2f& point) const;

		/*
		Re-orders the vertices in this simplex to follow the clockwise winding order.
		*/
		void PreserveWindingOrder();

	private:
		Set<sf::Vector2f> m_Vertices;
	};
}