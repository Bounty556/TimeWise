#pragma once

#include <Entities/Entity.h>

namespace Soul
{
	class Obstacle : public Entity
	{
	public:
		Obstacle(Context& context);

	private:
		virtual void UpdateSelf(float dt, Context& context) override;

		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}