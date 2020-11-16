#include "PlayerEntity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <Input/InputManager.h>
#include <ResourceManagers/TextureManager.h>

namespace Soul
{
	PlayerEntity::PlayerEntity(Context& context) :
		m_Sprite(*(context.TextureManager.RequestTexture("res/player.png"))),
		m_MoveSpeed(1.0f)
	{
		AddComponent(Partition(GravityComponent, this, 0.006f, 1.0f));
	}

	void PlayerEntity::UpdateSelf(float dt, Context& context)
	{
		if (context.InputManager.IsButtonDown(-1, "Right") || (context.InputManager.IsButtonDown(0, "Right") && context.InputManager.AxisPosition(0, "Right") > 0.0f))
		{
			move(m_MoveSpeed * dt, 0.0f);
		}

		if (context.InputManager.IsButtonDown(-1, "Left") || (context.InputManager.IsButtonDown(0, "Left") && context.InputManager.AxisPosition(0, "Left") < 0.0f))
		{
			move(-m_MoveSpeed * dt, 0.0f);
		}
	}

	void PlayerEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(m_Sprite, states);
	}
}