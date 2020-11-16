#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Entities/Entity.h>

namespace Soul
{
	class PlayerEntity : public Entity
	{
	public:
		PlayerEntity(Context& context);

	private:
		virtual void UpdateSelf(float dt, Context& context) override;
		
		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite m_Sprite;
		float m_MoveSpeed;
		float m_JumpStrength;
	};
}