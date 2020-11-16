#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

#include <Utility/Context.h>

namespace Soul
{
	class Entity;

	class Component
	{
	public:
		Component(Entity* entity);
		virtual ~Component();

		virtual void Update(float dt, Context& context) = 0;

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		virtual const char* GetType() const = 0;

	protected:
		Entity* m_AffectedEntity;
	};
}