#include "Platform.h"

#include <Components/Collider.h>
#include <Components/StaticCollider.h>
#include <Systems/PhysicsSystem.h>

namespace Soul
{
	Platform::Platform(Context& context) :
		Entity(context)
	{
		Collider* col = context.PhysicsSystem.CreateCollider(this, 500, 50);
		StaticCollider* staticCol = Partition(StaticCollider, this);

		staticCol->SetCollider(col);

		AddComponent(col);
		AddComponent(staticCol);
	}

	void Platform::UpdateSelf(float dt)
	{

	}

	void Platform::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}
}