#include "PhysicsComponent.h"

#include <Systems/PhysicsSystem.h>

namespace Soul
{
	PhysicsComponent::PhysicsComponent(Entity* entity, sf::FloatRect bounds, PhysicsSystem& system) :
		Component(entity),
		m_Bounds(bounds),
		m_System(system)
	{

	}

	PhysicsComponent::~PhysicsComponent()
	{
		m_System.RemovePhysicsComponent(this);
	}
}