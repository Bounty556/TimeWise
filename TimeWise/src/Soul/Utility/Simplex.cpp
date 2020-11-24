#include "Simplex.h"

#include <Utility/Math.h>

namespace Soul
{
	Simplex::Simplex() :
		m_Vertices(3)
	{
	}

	void Simplex::AddVertex(sf::Vector2f vertex)
	{
		m_Vertices.Add(vertex);
	}

	void Simplex::InsertVertex(unsigned int index, sf::Vector2f vertex)
	{
		m_Vertices.Insert(index, vertex);
	}

	bool Simplex::DoGJK(sf::Vector2f& direction)
	{
		switch (m_Vertices.Length())
		{
			case 1:
			{
				direction = Math::Normalize(-m_Vertices[0]);
			} break;

			case 3:
			{
				PreserveWindingOrder();

				sf::Vector2f perp0 = Math::Perpendicular(m_Vertices[1] - m_Vertices[0]);
				sf::Vector2f perp1 = Math::Perpendicular(m_Vertices[2] - m_Vertices[1]);
				sf::Vector2f perp2 = Math::Perpendicular(m_Vertices[0] - m_Vertices[2]);

				if (Math::Dot(-m_Vertices[0], perp0) <= 0.0f &&
					Math::Dot(-m_Vertices[1], perp1) <= 0.0f &&
					Math::Dot(-m_Vertices[2], perp2) <= 0.0f)
				{
					return true;
				}

				// Otherwise, this triangle does not contain the origin, so restart the simplex
				// with only the last vertex as the starting point.

				unsigned int closestIndex;
				sf::Vector2f normal;
				float dist;
				FindClosestEdge(normal, dist, closestIndex, sf::Vector2f(0.0f, 0.0f));

				sf::Vector2f temp0 = m_Vertices[closestIndex];
				sf::Vector2f temp1 = m_Vertices[(closestIndex + 1) % m_Vertices.Length()];
				m_Vertices.Clear();
				m_Vertices.Add(temp0);
				m_Vertices.Add(temp1);

				// Do the regular line case:
			}

			case 2:
			{
				// Check to see if we're on either side of the line
				sf::Vector2f line = m_Vertices[1] - m_Vertices[0];
				if (Math::Dot(-m_Vertices[1], line) < 0.0f)
				{
					// Search in that direction of the line
					sf::Vector2f perp = Math::Perpendicular(line);

					if (Math::Dot(perp, m_Vertices[1]) < 0.0f)
					{
						direction = Math::Normalize(perp);
					}
					else
					{
						direction = Math::Normalize(-perp);
					}
				}
				else
				{
					// We're somewhere past the last found vertex, search in the direction of
					// the origin.
					direction = Math::Normalize(-m_Vertices[1]);
				}
			} break;
		}

		return false;
	}

	void Simplex::FindClosestEdge(sf::Vector2f& outEdgeNormal, float& outEdgeDistance, unsigned int& outEdgeIndex, const sf::Vector2f& point) const
	{
		sf::Vector2f closestEdge(0.0f, 0.0f);
		float smallestDistance = 999999999.0f;
		unsigned int index = -1;

		for (unsigned int i = 0; i < m_Vertices.Length(); ++i)
		{
			sf::Vector2f edge(m_Vertices[(i + 1) % m_Vertices.Length()] - m_Vertices[i]);
			sf::Vector2f shiftedPoint(point - m_Vertices[i]);
			float distance = Math::Magnitude(Math::Reject(shiftedPoint, edge));

			if (distance < smallestDistance)
			{
				closestEdge = edge;
				smallestDistance = distance;
				index = i;
			}
		}

		outEdgeNormal = Math::Normal(closestEdge);
		outEdgeDistance = smallestDistance;
		outEdgeIndex = index;
	}

	void Simplex::PreserveWindingOrder()
	{
		Set<sf::Vector2f> oldVertices(m_Vertices.Length());
		for (unsigned int i = 0; i < m_Vertices.Length(); ++i)
		{
			oldVertices.Add(m_Vertices[i]);
		}

		m_Vertices.Clear();

		m_Vertices.Add(oldVertices[0]);
		m_Vertices.Add(oldVertices[1]);

		for (unsigned int i = 2; i < oldVertices.Length(); ++i)
		{
			sf::Vector2f newVertex = oldVertices[i];
			
			for (unsigned int j = m_Vertices.Length(); j > 0; --j)
			{
				sf::Vector2f prevPoint = m_Vertices[(j - 1) % m_Vertices.Length()];
				sf::Vector2f prevPrevPoint = m_Vertices[(j - 2) % m_Vertices.Length()];
				sf::Vector2f nextPoint = m_Vertices[j % m_Vertices.Length()];

				if (Math::Dot(Math::Perpendicular(prevPoint - prevPrevPoint), newVertex - prevPoint) <= 0.0f &&
					Math::Dot(Math::Perpendicular(newVertex - prevPoint), nextPoint - newVertex) <= 0.0f)
				{
					m_Vertices.Insert(j, newVertex);
				}
			}
		}
	}
}