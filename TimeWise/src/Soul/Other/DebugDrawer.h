#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <Memory/UniquePointer.h>

namespace Soul
{
	class DebugDrawer
	{
	public:
		DebugDrawer(unsigned int capacity);
		
		void AddLine(sf::Vector2f vertex1, sf::Vector2f vertex2);

		void Clear();

		void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		UniquePointer<sf::Vertex> m_Lines;

		unsigned int m_MaxShapes;

		unsigned int m_CurrentShapes;
	};
}