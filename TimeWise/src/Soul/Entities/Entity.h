#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <Components/Component.h>
#include <Structures/Vector.h>
#include <Utility/Context.h>

namespace Soul
{
	/*
	A base entity class. Entities can have components attached to them to modify or provide new
	behavior to them.
	*/
	class Entity : public sf::Drawable, public sf::Transformable
	{
	public:
		virtual ~Entity();

		void Update(float dt, Context& context);

		void SetVelocity(float dx, float dy);
		void Accelerate(float dx, float dy);

		void AddComponent(Component* component);

		Component* GetComponentOfType(const char* type) const;

		const sf::Vector2f& GetVelocity() const;

	private:
		void UpdateEntity(float dt, Context& context);
		virtual void UpdateSelf(float dt, Context& context) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	
	private:
		sf::Vector2f m_Velocity;
		Vector<Component*> m_Components;
	};
}