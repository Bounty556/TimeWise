#pragma once

#include <Components/CollisionHandler.h>
#include <Entities/Entity.h>

namespace Soul
{
	class Rigidbody : public CollisionHandler
	{
	public:
		Rigidbody(Entity* entity);

		// Inherited

		virtual void AddCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider) override;

		virtual void ResolveCollisions() override;

		virtual void Update(float dt) override;

	private:
		sf::Vector2f m_CorrectiveForces;
		sf::Vector2f m_NaturalForces;
	};
}