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

		virtual void Update(float dt, Context& context) = 0;

		virtual const char* GetType() const override = 0;

		virtual void HandleCollision(float dt, Context& context) = 0;

		const sf::FloatRect& GetBounds() const;

	protected:
		sf::FloatRect m_Bounds;
		PhysicsSystem& m_System;
	};
}