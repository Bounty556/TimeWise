#pragma once

#include <Components/CollisionHandler.h>
#include <Entities/Entity.h>

namespace Soul
{
	class StaticCollider : public CollisionHandler
	{
	public:
		StaticCollider(Entity* entity);

		// Inherited

		virtual void AddCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) override;

		virtual void ResolveCollisions() override;

		virtual void Update(float dt) override;
	};
}