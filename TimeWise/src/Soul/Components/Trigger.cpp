#include "Trigger.h"

#include <Utility/Hashes.h>

namespace Soul
{
	Trigger::Trigger(Entity* entity) :
		CollisionHandler(entity, "Trigger"),
		m_TagWhitelist(),
		m_IsTriggered(false),
		m_OtherCollider(nullptr)
	{

	}

	void Trigger::WhitelistTag(const char* tag)
	{
		m_TagWhitelist.Push(Hash(tag));
	}

	void Trigger::HandleCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{
		m_IsTriggered = true;
		m_OtherCollider = &collider;
	}

	void Trigger::Update(float dt)
	{
		m_IsTriggered = false;
		m_OtherCollider = nullptr;
	}

	Collider* Trigger::IsTriggered()
	{
		return m_OtherCollider;
	}
}