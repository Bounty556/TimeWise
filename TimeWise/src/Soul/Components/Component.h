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

		const Entity* GetEntity() const;

		virtual const char* GetType() const = 0;

	protected:
		Entity* m_AffectedEntity;
	};
}