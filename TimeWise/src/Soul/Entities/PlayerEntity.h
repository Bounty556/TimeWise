#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Components/GravityComponent.h>
#include <Entities/Entity.h>

namespace Soul
{
	class PlayerEntity : public Entity
	{
	public:
		PlayerEntity(Context& context);

		virtual void UpdateSelf(float dt, Context& context) override;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite m_Sprite;
		GravityComponent m_Gravity;
	};
}