#include "GravityComponent.h"

#include <Entities/Entity.h>

namespace Soul
{
	GravityComponent::GravityComponent(Entity* entity, float gravityStrength, float terminalVelocity) :
		Component(entity),
		m_GravityStrength(gravityStrength),
		m_TerminalVelocity(terminalVelocity)
	{

	}

	void GravityComponent::Update(float dt, Context& context)
	{
		m_AffectedEntity->Accelerate(0.0f, m_GravityStrength);

		if (m_AffectedEntity->GetVelocity().y >= m_TerminalVelocity)
		{
			m_AffectedEntity->SetVelocity(m_AffectedEntity->GetVelocity().x, m_TerminalVelocity);
		}
	}

	void GravityComponent::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}

	const char* GravityComponent::GetType() const
	{
		return "Gravity";
	}
}