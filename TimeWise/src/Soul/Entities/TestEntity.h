#pragma once

#include <Entities/Entity.h>

namespace Soul
{
	class TestEntity : public Entity
	{
	public:
		TestEntity(Context& context);

		virtual void UpdateSelf(float dt) override;

		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}