#include "PhysicsComponent.h"

namespace Soul
{
	PhysicsComponent::PhysicsComponent(Entity* entity, sf::FloatRect bounds) :
		Component(entity),
		m_Bounds(bounds)
	{

	}

	PhysicsComponent::~PhysicsComponent()
	{

	}
}