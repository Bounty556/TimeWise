#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include <Memory/UniquePointer.h>

namespace Soul
{
	class DebugDrawer
	{
	public:
		DebugDrawer(unsigned int capacity);
		
		void AddShape(sf::Vector2f position, sf::Vector2f size, float angle);

		void Clear();

		void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		UniquePointer<sf::RectangleShape> m_Shapes;

		unsigned int m_MaxShapes;

		unsigned int m_CurrentShapes;
	};
}