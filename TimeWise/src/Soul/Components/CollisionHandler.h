#pragma once

#include <Components/Component.h>
#include <Components/Collider.h>

namespace Soul
{
	class CollisionHandler : public Component
	{
	public:
		CollisionHandler(Entity* entity);
		virtual ~CollisionHandler();

		/*
		To be called from the entity's collider component. Sets Entity's velocity appropriately
		based on collision data.
		*/
		virtual void HandleCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) = 0;

		/*
		Handles gravity, angular momentum, drag, etc.
		*/
		virtual void Update(float dt) = 0;

		void SetCollider(Collider* collider);

	protected:
		Collider* m_Collider;
	};
}