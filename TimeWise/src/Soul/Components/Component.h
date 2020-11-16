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

		virtual const char* GetType() const = 0;

		unsigned long long GetHandle() const;

	protected:
		Entity* m_AffectedEntity;
		unsigned long long m_Handle;
	};
}