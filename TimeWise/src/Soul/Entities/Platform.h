#pragma once

#include <Entities/Entity.h>

namespace Soul
{
	class Platform : public Entity
	{
	public:
		Platform(Context& context);

	private:
		virtual void UpdateSelf(float dt) override;

		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}