#pragma once

#include <Components/PhysicsComponent.h>

namespace Soul
{
	class Rigidbody : public PhysicsComponent
	{
	public:
		Rigidbody(Entity* entity, sf::FloatRect bounds, PhysicsSystem& system);

		void SetStatic(bool isStatic);
		
		void SetGravity(float gravity);

		void SetTerminalVelocity(float terminalVelocity);

		virtual void Update(float dt, Context& context) override;

		virtual const char* GetType() const override;

		virtual void HandleCollision(float dt, Context& context) override;

	private:
		bool m_IsStatic;
		float m_Gravity;
		float m_TerminalVelocity;
	};
}