#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Entities/Entity.h>

namespace Soul
{
	class PlayerEntity : public Entity
	{
	public:
		PlayerEntity(Context& context);

		virtual void Update(float dt, Context& context) override;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite m_Sprite;
	};
}