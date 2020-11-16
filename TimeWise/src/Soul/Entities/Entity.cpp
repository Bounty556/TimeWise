#include "Entity.h"

#include <cstring>

namespace Soul
{
	Entity::~Entity()
	{
	}

	void Entity::Update(float dt, Context& context)
	{
		move(m_Velocity * dt);

		UpdateSelf(dt, context);
	}

	void Entity::SetVelocity(float dx, float dy)
	{
		m_Velocity = sf::Vector2f(dx, dy);
	}

	void Entity::Accelerate(float dx, float dy)
	{
		m_Velocity += sf::Vector2f(dx, dy);
	}

	const sf::Vector2f& Entity::GetVelocity() const
	{
		return m_Velocity;
	}

	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		DrawSelf(target, states);
	}
}