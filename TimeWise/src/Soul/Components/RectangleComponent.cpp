#include "RectangleComponent.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace Soul
{
	RectangleComponent::RectangleComponent(Entity* entity, sf::Vector2f size) :
		Component(entity),
		m_Rect(size)
	{

	}

	void RectangleComponent::Update(float dt, Context& context)
	{

	}

	void RectangleComponent::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Rect, states);
	}

	const char* RectangleComponent::GetType() const
	{
		return "Rectangle";
	}
}