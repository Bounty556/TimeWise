#pragma once

#include <Components/CollisionHandler.h>
#include <Entities/Entity.h>

namespace Soul
{
	class Rigidbody : public CollisionHandler
	{
	public:
		Rigidbody(Entity* entity);

		/*
		To be called from the entity's collider component. Sets Entity's velocity appropriately
		based on collision data.
		*/
		virtual void HandleCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) override;

		/*
		Handles gravity, angular momentum, drag, etc.
		*/
		virtual void Update(float dt) override;
	};
}