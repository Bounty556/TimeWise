#include "TestEntity.h"

#include <Components/Rigidbody.h>
#include <Components/Collider.h>
#include <Systems/PhysicsSystem.h>

namespace Soul
{
	TestEntity::TestEntity(Context& context) :
		Entity(context)
	{
		Rigidbody* rb = Partition(Rigidbody, this, true, 0.0f, 0.5f);
		Collider* col = context.PhysicsSystem.CreateCollider(this, 3, sf::Vector2f(-10.0f, -10.0f), sf::Vector2f(10.0f, -10.0f), sf::Vector2f(0.0f, 10.0f));

		rb->SetCollider(col);

		col->SetMass(5.0f);
		col->SetBounciness(0.1f);
		col->SetFriction(0.45f);

		AddComponent(rb);
		AddComponent(col);
	}

	void TestEntity::UpdateSelf(float dt)
	{

	}

	void TestEntity::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}
}