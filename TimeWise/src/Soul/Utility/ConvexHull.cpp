#include "ConvexHull.h"

namespace Soul
{
	ConvexHull::ConvexHull(const UniquePointer<sf::Vector2f>& vertices, unsigned int vertexCount) :
		m_Vertices(nullptr)
	{
		GenerateHull(vertices, vertexCount);
	}

	void ConvexHull::GenerateHull(const UniquePointer<sf::Vector2f>& vertices, unsigned int vertexCount)
	{
		UniquePointer<sf::Vector2f> tempVertices(PartitionArray(sf::Vector2f, vertexCount));
		unsigned int hullVertices = 0;

		// Find min and max x vertices
		sf::Vector2f minX(9999999.0f, 9999999.0f);
		sf::Vector2f maxX(-9999999.0f, -9999999.0f);
		for (unsigned int i = 0; i < vertexCount; ++i)
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

		while (true)
		{
			// TODO: Grab rest of points
		}
	}
}