#include "Entity.h"

#include <cstring>

#include <Structures/CommandQueue.h>
#include <Utility/Hashes.h>
#include <Utility/Math.h>

namespace Soul
{
	Entity::Entity(Context& context) :
		m_Context(context),
		m_Tags(),
		m_Components(),
		m_Velocity(0.0f, 0.0f)
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

	void Entity::AddTag(const char* tag)
	{
		m_Tags.Push(Hash(tag));
	}

	bool Entity::HasTag(unsigned long long tag)
	{
		for (unsigned int i = 0; i < m_Tags.Length(); ++i)
		{
			if (m_Tags[i] == tag)
			{
				return true;
			}
		}

		return false;
	}

	void Entity::Update(float dt)
	{
		UpdateSelf(dt);

		Math::Clamp(m_Velocity.x, -1000.0f, 1000.0f);
		Math::Clamp(m_Velocity.y, -1000.0f, 1000.0f);

		move(m_Velocity * dt);
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
			if (Hash(componentType) == m_Components[i]->GetType())
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