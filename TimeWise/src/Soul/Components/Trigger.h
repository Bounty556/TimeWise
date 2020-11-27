#pragma once

#include <Components/CollisionHandler.h>
#include <Entities/Entity.h>

namespace Soul
{
	class Trigger : public CollisionHandler
	{
	public:
		Trigger(Entity* entity);

		virtual void HandleCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) override;

		virtual void Update(float dt) override;

		// Getters

		Collider* IsTriggered();

	private:
		bool m_IsTriggered;
		Collider* m_OtherCollider;
	};
}