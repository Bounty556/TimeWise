#include "Entity.h"

namespace Soul
{
	Entity::~Entity()
	{

	}
	

	void Entity::Update(float dt, Context& context)
	{
		UpdateSelf(dt, context);
		UpdateEntity(dt);
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

	void Entity::UpdateEntity(float dt)
	{
		move(m_Velocity * dt);
	}
}