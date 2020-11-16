#pragma once

#include <Components/Component.h>

namespace Soul
{
	class GravityComponent : public Component
	{
	public:
		GravityComponent(Entity* entity, float gravityStrength, float terminalVelocity);

		virtual void Update(float dt, Context& context) override;

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual const char* GetType() const override;

	private:
		float m_GravityStrength;
		float m_TerminalVelocity;
	};
}