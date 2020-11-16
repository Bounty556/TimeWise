#include "Component.h"

namespace Soul
{
	Component::Component(Entity* entity) :
		m_AffectedEntity(entity)
	{

	}

	Component::~Component()
	{

	}
}