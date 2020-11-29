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

		void BlacklistTag(const char* tag);

		Collider* ConsumeCollision();

		// Inherited

		virtual void AddCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) override;

		virtual void ResolveCollisions() override;

		virtual void Update(float dt) override;

		// Getters

		Collider* IsTriggered() const;

	private:
		Vector<unsigned long long> m_TagBlacklist;
		bool m_IsTriggered;
		Collider* m_OtherCollider;
	};
}