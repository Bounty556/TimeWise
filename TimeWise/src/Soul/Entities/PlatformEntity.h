#pragma once

#include <Entities/Entity.h>
#include <Utility/Context.h>

namespace Soul
{
	class PlatformEntity : public Entity
	{
	public:
		PlatformEntity(Context& context, sf::Vector2f size);

		virtual void UpdateSelf(float dt, Context& context);
		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}