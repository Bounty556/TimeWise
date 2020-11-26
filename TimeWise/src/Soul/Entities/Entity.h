#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <Components/Component.h>
#include <Structures/Vector.h>
#include <Utility/Context.h>
#include <Strings/String.h>

namespace Soul
{
	/*
	A base entity class. Entities can have components attached to them to
	modify or provide new behavior to them.
	*/
	class Entity : public sf::Drawable, public sf::Transformable
	{
	public:
		Entity(Context& context);
		virtual ~Entity();

		void Update(float dt);

		void SetVelocity(float dx, float dy);
		void SetVelocity(sf::Vector2f dv);
		void Accelerate(float dx, float dy);
		void Accelerate(sf::Vector2f da);

		const sf::Vector2f& GetVelocity() const;

		void AddComponent(Component* component);

		Component* GetComponent(const String& componentType);

	private:
		virtual void UpdateSelf(float dt) = 0;

		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	protected:
		Context& m_Context;

	private:
		sf::Vector2f m_Velocity;
		Vector<Component*> m_Components;
	};
}