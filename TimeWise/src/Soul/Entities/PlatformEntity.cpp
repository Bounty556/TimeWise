#include "PlatformEntity.h"

#include <Components/RectangleComponent.h>

namespace Soul
{
	PlatformEntity::PlatformEntity(Context& context, sf::Vector2f size)
	{
		AddComponent(Partition(RectangleComponent, this, size));
	}

	void PlatformEntity::UpdateSelf(float dt, Context& context)
	{

	}

	void PlatformEntity::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}
}