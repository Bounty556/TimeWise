#include "Component.h"

#include <Utility/Hashes.h>

namespace Soul
{
	Component::Component(Entity* entity, const char* type) :
		m_AffectedEntity(entity),
		m_HashedType(Hash(type))
	{

	}

	Component::~Component()
	{

	}

	const Entity* Component::GetEntity() const
	{
		return m_AffectedEntity;
	}

	const unsigned long long Component::GetType() const
	{
		return m_HashedType;
	}

	bool Component::CleanUp(Context& context)
	{
		return true;
	}
}