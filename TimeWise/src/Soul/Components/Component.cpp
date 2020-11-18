#include "Component.h"

#include <Utility/Handle.h>

namespace Soul
{
	Component::Component(Entity* entity) :
		m_AffectedEntity(entity)
	{

	}

	Component::~Component()
	{

	}

	const Entity* Component::GetEntity() const
	{
		return m_AffectedEntity;
	}

	bool Component::CleanUp(Context& context)
	{
		return true;
	}
}