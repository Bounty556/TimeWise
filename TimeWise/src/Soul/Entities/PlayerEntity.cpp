#include "PlayerEntity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <Components/Collider.h>
#include <Components/Rigidbody.h>
#include <Input/InputManager.h>
#include <ResourceManagers/TextureManager.h>
#include <Systems/PhysicsSystem.h>

namespace Soul
{
	PlayerEntity::PlayerEntity(Context& context) :
		Entity(context),
		m_Sprite(*(m_Context.TextureManager.RequestTexture("res/player.png"))),
		m_MoveSpeed(0.5f),
		m_JumpStrength(1.5f)
	{
		Collider* col = context.PhysicsSystem.CreateCollider(this, 4, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 0.0f), sf::Vector2f(32.0f, 64.0f), sf::Vector2f(0.0f, 64.0f));
		Rigidbody* rb = Partition(Rigidbody, this);

		rb->SetCollider(col);

		col->SetBounciness(0.0f);
		col->SetFriction(0.5f);
		col->SetIsSolid(true);

		AddComponent(col);
		AddComponent(rb);
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

		if (m_Context.InputManager.WasButtonPressed(-1, "Jump"))
		{
			Collider* col = (Collider*)GetComponent("Collider");
			col->ApplyForce(sf::Vector2f(0.0f, -m_JumpStrength));
		}
	}

	void PlayerEntity::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Sprite, states);
	}
}