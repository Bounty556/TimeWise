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

		/*
		Does any final necessary cleanup for this component. Returns true if the owning entity
		can free it, and false if another system cleans this component up.
		*/
		virtual bool CleanUp(Context& context);

	protected:
		Entity* m_AffectedEntity;
	};
}