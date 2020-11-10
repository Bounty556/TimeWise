#include "RectangleNode.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace Soul
{
	RectangleNode::RectangleNode(float width, float height, sf::Color color) :
		m_Rect(sf::Vector2f(width, height))
	{
		m_Rect.setFillColor(color);
	}

	void RectangleNode::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Rect, states);
	}
}