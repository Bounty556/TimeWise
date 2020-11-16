#pragma once

#include <Entities/Entity.h>
#include <Utility/Context.h>

namespace Soul
{
	class Component
	{
	public:
		Component(Entity* entity);
		virtual ~Component();

		virtual void Update(float dt, Context& context) = 0;

	protected:
		Entity* m_AffectedEntity;
	};
}