#include "Entity.h"

#include <cstring>

#include <Structures/CommandQueue.h>
#include <Utility/Math.h>

namespace Soul
{
	Entity::Entity(Context& context) :
		m_Velocity(0.0f, 0.0f),
		m_Components(8),
		m_Context(context)
	{

	}

	Entity::~Entity()
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			if (m_Components[i]->CleanUp(m_Context))
			{
				MemoryManager::FreeMemory(m_Components[i]);
			}
		}
	}

	void Entity::Update(float dt)
	{
		Math::Clamp(m_Velocity.x, -1000.0f, 1000.0f);
		Math::Clamp(m_Velocity.y, -1000.0f, 1000.0f);

		move(m_Velocity * dt);

		UpdateSelf(dt);
	}

	void Entity::SetVelocity(float dx, float dy)
	{
		m_Velocity = sf::Vector2f(dx, dy);
	}

	void Entity::SetVelocity(sf::Vector2f dv)
	{
		m_Velocity = dv;
	}

	void Entity::Accelerate(float dx, float dy)
	{
		m_Velocity += sf::Vector2f(dx, dy);
	}

	void Entity::Accelerate(sf::Vector2f da)
	{
		m_Velocity += da;
	}

	const sf::Vector2f& Entity::GetVelocity() const
	{
		return m_Velocity;
	}

	void Entity::AddComponent(Component* component)
	{
		m_Components.Push(component);
	}

	Component* Entity::GetComponent(const String& componentType)
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			if (componentType.CompareTo(m_Components[i]->GetType()) == 0)
			{
				return m_Components[i];
			}
		}
		
		return nullptr;
	}

	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		DrawSelf(target, states);
	}
}