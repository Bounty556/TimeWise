#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <Nodes/Node.h>

namespace Soul
{
	class RectangleNode : public Node
	{
	public:
		RectangleNode(float width = 0, float height = 0, sf::Color color = sf::Color::White);

	private:
		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::RectangleShape m_Rect;
	};
}