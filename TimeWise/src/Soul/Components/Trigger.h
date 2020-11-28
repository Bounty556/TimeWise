#pragma once

#include <Components/CollisionHandler.h>
#include <Entities/Entity.h>
#include <Structures/Vector.h>

namespace Soul
{
	class Trigger : public CollisionHandler
	{
	public:
		Trigger(Entity* entity);

		void WhitelistTag(const char* tag);

		// Inherited

		virtual void HandleCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) override;

		virtual void Update(float dt) override;

		// Getters

		Collider* IsTriggered();

	private:
		Vector<unsigned long long> m_TagWhitelist;
		bool m_IsTriggered;
		Collider* m_OtherCollider;
	};
}