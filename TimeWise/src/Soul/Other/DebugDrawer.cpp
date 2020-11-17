#include "DebugDrawer.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <Memory/MemoryManager.h>

namespace Soul
{
	DebugDrawer::DebugDrawer(unsigned int capacity) :
		m_Lines(PartitionArray(sf::Vertex, capacity)),
		m_MaxShapes(capacity),
		m_CurrentShapes(0)
	{
		for (unsigned int i = 0; i < m_MaxShapes; ++i)
		{
			m_Lines[i] = sf::Vertex();
		}
	}

	void DebugDrawer::AddLine(sf::Vector2f vertex1, sf::Vector2f vertex2)
	{
		if (m_CurrentShapes != m_MaxShapes)
		{
			m_Lines[m_CurrentShapes++] = sf::Vertex(vertex1);
			m_Lines[m_CurrentShapes++] = sf::Vertex(vertex2);
		}
	}

	void DebugDrawer::Clear()
	{
		m_CurrentShapes = 0;
	}

	void DebugDrawer::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (unsigned int i = 0; i < m_CurrentShapes; i += 2)
		{
			target.draw(&m_Lines[i], 2, sf::Lines);
		}
	}
}