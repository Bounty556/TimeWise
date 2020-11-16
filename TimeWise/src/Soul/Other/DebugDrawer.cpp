#include "DebugDrawer.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <Memory/MemoryManager.h>

namespace Soul
{
	DebugDrawer::DebugDrawer(unsigned int capacity) :
		m_Shapes(PartitionArray(sf::RectangleShape, capacity)),
		m_MaxShapes(capacity),
		m_CurrentShapes(0)
	{
		for (unsigned int i = 0; i < m_MaxShapes; ++i)
		{
			new (&(m_Shapes[i])) sf::RectangleShape();
		}
	}

	void DebugDrawer::AddShape(sf::Vector2f position, sf::Vector2f size, float angle)
	{
		if (m_CurrentShapes != m_MaxShapes)
		{
			sf::RectangleShape& shape = m_Shapes[m_CurrentShapes];

			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineThickness(1.0f);
			shape.setOutlineColor(sf::Color::Red);
			shape.setPosition(position);
			shape.setSize(size);
			shape.setRotation(angle);

			++m_CurrentShapes;
		}
	}

	void DebugDrawer::Clear()
	{
		m_CurrentShapes = 0;
	}

	void DebugDrawer::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (unsigned int i = 0; i < m_CurrentShapes; ++i)
		{
			target.draw(m_Shapes[i], states);
		}
	}
}