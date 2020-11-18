#pragma once

#include <Entities/Entity.h>

namespace Soul
{
	class TestEntity2 : public Entity
	{
	public:
		TestEntity2(Context& context);

		virtual void UpdateSelf(float dt) override;

		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}