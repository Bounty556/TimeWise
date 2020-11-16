#pragma once

#include <SFML/Graphics/Rect.hpp>

#include <Components/Component.h>

namespace Soul
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent(Entity* entity, sf::FloatRect bounds);
		virtual ~PhysicsComponent();

		virtual const char* GetType() const override = 0;

		virtual void HandleCollision() = 0;

	private:
		sf::FloatRect m_Bounds;
		float m_Angle;
	};
}