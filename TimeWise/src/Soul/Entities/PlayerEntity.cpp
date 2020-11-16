#include "PlayerEntity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <Input/InputManager.h>
#include <ResourceManagers/TextureManager.h>
#include <Systems/PhysicsSystem.h>
#include <Components/Rigidbody.h>

namespace Soul
{
	PlayerEntity::PlayerEntity(Context& context) :
		m_Sprite(*(context.TextureManager.RequestTexture("res/player.png"))),
		m_MoveSpeed(0.5f)
	{
		Rigidbody* rb = context.PhysicsSystem.CreatePhysicsComponent<Rigidbody>(this, sf::FloatRect(0.0f, 0.0f, 32.0f, 64.0f));
		rb->SetStatic(false);
		rb->SetGravity(0.008f);
		rb->SetTerminalVelocity(1.0f);
		AddComponent(rb);
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

	void PlayerEntity::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Sprite, states);
	}
}