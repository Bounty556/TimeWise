#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Components/Trigger.h>
#include <Entities/Entity.h>

namespace Soul
{
	class PlayerEntity : public Entity
	{
	public:
		PlayerEntity(Context& context);

	private:
		virtual void UpdateSelf(float dt) override;
		
		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite m_Sprite;
		Trigger* m_JumpTrigger;
		float m_MoveSpeed;
		float m_JumpStrength;
		float m_JumpCount;
	};
}