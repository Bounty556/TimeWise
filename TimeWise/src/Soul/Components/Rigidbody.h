#pragma once

#include <Components/PhysicsComponent.h>

namespace Soul
{
	class Rigidbody : public PhysicsComponent
	{
	public:
		Rigidbody(Entity* entity, sf::FloatRect bounds, PhysicsSystem& system);

		void SetStatic(bool isStatic);

		virtual const char* GetType() const override;

		virtual void HandleCollision(float dt, Context& context) override;

	private:
		bool m_IsStatic;
	};
}