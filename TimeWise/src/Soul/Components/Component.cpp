#include "Component.h"

#include <Utility/Handle.h>

namespace Soul
{
	Component::Component(Entity* entity) :
		m_AffectedEntity(entity),
		m_Handle(GetUniqueHandle())
	{

	}

	Component::~Component()
	{

	}

	unsigned long long Component::GetHandle() const
	{
		return m_Handle;
	}
}