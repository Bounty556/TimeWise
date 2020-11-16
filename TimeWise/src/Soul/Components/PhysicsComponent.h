#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <Components/Component.h>

namespace Soul
{
	class PhysicsSystem;

	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(Entity* entity, sf::FloatRect bounds, PhysicsSystem& system);
		virtual ~PhysicsComponent();

		virtual const char* GetType() const override = 0;

		virtual void HandleCollision(float dt, Context& context) = 0;

	protected:
		sf::FloatRect m_Bounds;
		float m_Angle;
		PhysicsSystem& m_System;
	};
}