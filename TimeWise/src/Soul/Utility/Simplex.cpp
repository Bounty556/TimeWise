#include "Simplex.h"

#include <Utility/Math.h>

namespace Soul
{
	Simplex::Simplex() :
		m_Vertices(PartitionArray(sf::Vector2f, 3)),
		m_VertexCount(0)
	{

	}

	void Simplex::AddVertex(sf::Vector2f vertex)
	{
		m_Vertices[m_VertexCount++] = vertex;
	}

	bool Simplex::DoGJK(sf::Vector2f& direction)
	{
		switch (m_VertexCount)
		{
			case 1:
			{
				direction = Math::Normalize(-m_Vertices[0]);
			} break;

			case 2:
			{
				// Check to see if we're on either side of the line
				if (Math::Dot(-m_Vertices[1], m_Vertices[1] - m_Vertices[0]) < 0)
				{
					// Search in that direction of the line
					sf::Vector2f line = m_Vertices[1] - m_Vertices[0];
					sf::Vector2f perp = Math::Perpendicular(line);

					if (Math::Dot(perp, m_Vertices[1]) < 0)
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
					// We're somewhere past the last found vertex, search in the direction of the
					// origin.
					direction = Math::Normalize(-m_Vertices[1]);
				}
			} break;

			case 3:
			{
				// Check to see if we're in the triangle
				if (Math::Dot(-m_Vertices[1], m_Vertices[1] - m_Vertices[0]) < 0 && Math::Dot(-m_Vertices[2], m_Vertices[2] - m_Vertices[1]) < 0 && Math::Dot(-m_Vertices[0], m_Vertices[0] - m_Vertices[2]) < 0)
				{
					return true;
				}

				// Otherwise, this triangle does not contain the origin, so restart the simplex
				// with only the last vertex as the starting point.
				m_VertexCount = 1;
				m_Vertices[0] = m_Vertices[2];
				direction = Math::Normalize(-m_Vertices[0]);
			} break;
		}

		return false;
	}
}