#include "PlayerEntity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <Input/InputManager.h>
#include <ResourceManagers/TextureManager.h>

namespace Soul
{
	PlayerEntity::PlayerEntity(Context& context) :
		Entity(context),
		m_Sprite(*(m_Context.TextureManager.RequestTexture("res/player.png"))),
		m_MoveSpeed(0.5f),
		m_JumpStrength(0.5f)
	{
	}

	void PlayerEntity::UpdateSelf(float dt)
	{
		if (m_Context.InputManager.IsButtonDown(-1, "Right") || (m_Context.InputManager.IsButtonDown(0, "Right") && m_Context.InputManager.AxisPosition(0, "Right") > 0.0f))
		{
			move(m_MoveSpeed * dt, 0.0f);
		}

		if (m_Context.InputManager.IsButtonDown(-1, "Left") || (m_Context.InputManager.IsButtonDown(0, "Left") && m_Context.InputManager.AxisPosition(0, "Left") < 0.0f))
		{
			move(-m_MoveSpeed * dt, 0.0f);
		}

		if (m_Context.InputManager.WasButtonPressed(-1, "Jump") || m_Context.InputManager.WasButtonPressed(0, "Jump"))
		{
			SetVelocity(GetVelocity().x, -m_JumpStrength);
		}
	}

	void PlayerEntity::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Sprite, states);
	}
}