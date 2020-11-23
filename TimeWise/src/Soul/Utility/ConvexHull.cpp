#include "ConvexHull.h"

#include <Structures/Vector.h>
#include <Utility/Math.h>

namespace Soul
{
	ConvexHull::ConvexHull(const Set<sf::Vector2f>& vertices) :
		m_Vertices(nullptr)
	{
		GenerateHull(vertices);
	}

	void ConvexHull::GenerateHull(const Set<sf::Vector2f>& vertices)
	{
		Vector<sf::Vector2f> tempVertices(vertices.Length());
		unsigned int hullVertices = 0;

		// Find min and max x vertices
		sf::Vector2f minX(9999999.0f, 9999999.0f);
		sf::Vector2f maxX(-9999999.0f, -9999999.0f);
		for (unsigned int i = 0; i < vertices.Length(); ++i)
		{
			if (vertices[i].x < minX.x)
			{
				minX = vertices[i];
			}
			else if (vertices[i].x = minX.x && vertices[i].y < minX.y)
			{
				minX = vertices[i];
			}

			if (vertices[i].x > maxX.x)
			{
				maxX = vertices[i];
			}
			else if (vertices[i].x = maxX.x && vertices[i].y > maxX.y)
			{
				maxX = vertices[i];
			}
		}

		tempVertices.Push(minX);
		tempVertices.Push(maxX);

		unsigned int currentVertex = 0;
		while (true)
		{
			sf::Vector2f line(tempVertices[(currentVertex + 1) % tempVertices.Length()] - tempVertices[currentVertex]);
			sf::Vector2f direction = Math::Perpendicular(line);

			bool found = false;
			float magnitude = 0.0f;
			sf::Vector2f point;

			for (unsigned int i = 0; i < vertices.Length(); ++i)
			{
				float mag = Math::Dot(vertices[i] - tempVertices[currentVertex], direction);
				if (mag > magnitude)
				{
					magnitude = mag;
					point = vertices[i];
					found = true;
				}
			}

			if (found)
			{
				tempVertices.Insert(currentVertex + 1, point);
			}
			else
			{
				++currentVertex;
			}

			if (currentVertex == tempVertices.Length() - 1)
			{
				break;
			}
		}

		m_Vertices = PartitionArray(sf::Vector2f, tempVertices.Length());

		for (unsigned int i = 0; i < tempVertices.Length(); ++i)
		{
			new (&m_Vertices[i]) sf::Vector2f(tempVertices[i]);
		}
	}
}