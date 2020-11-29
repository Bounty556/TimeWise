#include "Trigger.h"

#include <Utility/Hashes.h>

namespace Soul
{
	Trigger::Trigger(Entity* entity) :
		CollisionHandler(entity, "Trigger"),
		m_TagBlacklist(),
		m_IsTriggered(false),
		m_OtherCollider(nullptr)
	{

	}

	void Trigger::BlacklistTag(const char* tag)
	{
		m_TagBlacklist.Push(Hash(tag));
	}

	Collider* Trigger::ConsumeCollision()
	{
		Collider* col = m_OtherCollider;
		m_IsTriggered = false;
		m_OtherCollider = nullptr;

		return col;
	}

	void Trigger::AddCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{
		for (unsigned int i = 0; i < m_TagBlacklist.Length(); ++i)
		{
			if (collider.GetEntity()->HasTag(m_TagBlacklist[i]))
			{
				return;
			}
		}
		m_IsTriggered = true;
		m_OtherCollider = &collider;
	}
	
	void Trigger::ResolveCollisions()
	{

	}

	void Trigger::Update(float dt)
	{
	}

	Collider* Trigger::IsTriggered() const
	{
		return m_OtherCollider;
	}
}