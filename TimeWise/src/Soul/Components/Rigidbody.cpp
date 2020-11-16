#include "Rigidbody.h"

#include <Entities/Entity.h>
#include <Other/DebugDrawer.h>

namespace Soul
{
	Rigidbody::Rigidbody(Entity* entity, sf::FloatRect bounds, PhysicsSystem& system) :
		PhysicsComponent(entity, bounds, system),
		m_IsStatic(true)
	{

	}

	void Rigidbody::SetStatic(bool isStatic)
	{
		m_IsStatic = isStatic;
	}

	const char* Rigidbody::GetType() const
	{
		return "Rigidbody";
	}

	void Rigidbody::HandleCollision(float dt, Context& context)
	{
		sf::Vector2f pos = m_AffectedEntity->getPosition();
		pos.x += m_Bounds.left;
		pos.y += m_Bounds.top;
		sf::Vector2f size(m_Bounds.width, m_Bounds.height);
		context.DebugDrawer.AddShape(pos, size, m_Angle);
	}
}