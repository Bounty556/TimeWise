#include "Obstacle.h"

#include <Components/Rigidbody.h>
#include <Systems/PhysicsSystem.h>

namespace Soul
{
	Obstacle::Obstacle(Context& context)
	{
		Rigidbody* rb = context.PhysicsSystem.CreatePhysicsComponent<Rigidbody>(this, sf::FloatRect(0.0f, 0.0f, 50.0f, 50.0f));
		
		rb->SetStatic(true);

		AddComponent(rb);
	}

	void Obstacle::UpdateSelf(float dt, Context& context)
	{

	}

	void Obstacle::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}
}