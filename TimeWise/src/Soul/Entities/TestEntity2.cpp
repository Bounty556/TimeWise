#include "TestEntity2.h"

#include <Components/StaticCollider.h>
#include <Components/Collider.h>
#include <Systems/PhysicsSystem.h>

namespace Soul
{
	TestEntity2::TestEntity2(Context& context) :
		Entity(context)
	{
		StaticCollider* statCol = Partition(StaticCollider, this);
		Collider* col = context.PhysicsSystem.CreateCollider(this, 4, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(context.WindowWidth - 100.0f, 0.0f), sf::Vector2f(context.WindowWidth - 100.0f, 150.0f), sf::Vector2f(0.0f, 150.0f));

		statCol->SetCollider(col);

		AddComponent(statCol);
		AddComponent(col);
	}

	void TestEntity2::UpdateSelf(float dt)
	{

	}

	void TestEntity2::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}
}