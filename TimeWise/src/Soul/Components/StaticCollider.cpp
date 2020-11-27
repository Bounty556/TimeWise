#include "StaticCollider.h"

namespace Soul
{
	StaticCollider::StaticCollider(Entity* entity) :
		CollisionHandler(entity, "Static Collider")
	{

	}

	void StaticCollider::HandleCollision(float dt, const sf::Vector2f& contactPoint, const sf::Vector2f& correction, Collider& collider)
	{

	}

	void StaticCollider::Update(float dt)
	{

	}
}