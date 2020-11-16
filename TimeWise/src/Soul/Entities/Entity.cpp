#include "Entity.h"

#include <cstring>

namespace Soul
{
	Entity::~Entity()
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			MemoryManager::FreeMemory(m_Components[i]);
		}
	}

	void Entity::Update(float dt, Context& context)
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			m_Components[i]->Update(dt, context);
		}

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

	void Entity::AddComponent(Component* component)
	{
		m_Components.Push(component);
	}

	Component* Entity::GetComponentOfType(const char* type) const
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			if (strcmp(m_Components[i]->GetType(), type))
			{
				return m_Components[i];
			}
		}

		return nullptr;
	}

	const sf::Vector2f& Entity::GetVelocity() const
	{
		return m_Velocity;
	}

	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			m_Components[i]->Draw(target, states);
		}

		DrawSelf(target, states);
	}
}