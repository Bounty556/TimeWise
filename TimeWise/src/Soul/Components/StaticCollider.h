#pragma once

#include <Components/CollisionHandler.h>
#include <Entities/Entity.h>

namespace Soul
{
	class StaticCollider : public CollisionHandler
	{
	public:
		StaticCollider(Entity* entity);

		virtual void HandleCollision(const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) override;

		virtual void Update(float dt) override;

		virtual const char* GetType() const override;
	};
}