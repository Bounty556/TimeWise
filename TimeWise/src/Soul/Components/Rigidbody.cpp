#include "Rigidbody.h"

#include <Entities/Entity.h>
#include <Other/DebugDrawer.h>

namespace Soul
{
	Rigidbody::Rigidbody(Entity* entity, sf::FloatRect bounds, PhysicsSystem& system) :
		PhysicsComponent(entity, bounds, system),
		m_IsStatic(true),
		m_Gravity(0.0f),
		m_TerminalVelocity(0.0f)
	{

	}

	void Rigidbody::SetStatic(bool isStatic)
	{
		m_IsStatic = isStatic;
	}

	void Rigidbody::SetGravity(float gravity)
	{
		m_Gravity = gravity;
	}

	void Rigidbody::SetTerminalVelocity(float terminalVelocity)
	{
		m_TerminalVelocity = terminalVelocity;
	}

	void Rigidbody::Update(float dt, Context& context)
	{
		if (!m_IsStatic)
		{
			m_AffectedEntity->Accelerate(0.0f, m_Gravity);
			if (m_AffectedEntity->GetVelocity().y > m_TerminalVelocity)
			{
				m_AffectedEntity->SetVelocity(m_AffectedEntity->GetVelocity().x, m_TerminalVelocity);
			}
		}

		sf::Vector2f pos(m_Bounds.left, m_Bounds.top);
		pos += m_AffectedEntity->getPosition();
		sf::Vector2f size(m_Bounds.width, m_Bounds.height);
		context.DebugDrawer.AddShape(pos, size, 0.0f);
	}

	const char* Rigidbody::GetType() const
	{
		return "Rigidbody";
	}

	void Rigidbody::HandleCollision(float dt, Context& context)
	{
		if (!m_IsStatic)
		{
			m_AffectedEntity->SetVelocity(0.0f, 0.0f);
		}
	}
}