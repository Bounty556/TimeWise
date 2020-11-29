#include "PlayerEntity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <Components/Collider.h>
#include <Components/Rigidbody.h>
#include <Input/InputManager.h>
#include <ResourceManagers/TextureManager.h>
#include <Systems/PhysicsSystem.h>

namespace Soul
{
	PlayerEntity::PlayerEntity(Context& context, unsigned int controller) :
		Entity(context),
		m_Sprite(*(m_Context.TextureManager.RequestTexture("res/player.png"))),
		m_JumpTrigger(nullptr),
		m_MoveSpeed(0.5f),
		m_JumpStrength(1.5f),
		m_JumpCount(1),
		m_Controller(controller)
	{
		Collider* col = context.PhysicsSystem.CreateCollider(this, 4, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 0.0f), sf::Vector2f(32.0f, 64.0f), sf::Vector2f(0.0f, 64.0f));
		Rigidbody* rb = Partition(Rigidbody, this);

		Collider* jumpCol = context.PhysicsSystem.CreateCollider(this, 3, sf::Vector2f(1.0f, 0.0f), sf::Vector2f(16.0f, -16.0f), sf::Vector2f(31.0f, 0.0f));
		Trigger* jumpTrigger = Partition(Trigger, this);

		rb->SetCollider(col);

		col->SetBounciness(0.0f);
		col->SetFriction(0.5f);
		col->SetIsSolid(true);

		String blackListedTag = "Player";
		blackListedTag += String::IntToString(controller);
		jumpTrigger->SetCollider(jumpCol);
		jumpTrigger->BlacklistTag(blackListedTag.GetCString());

		jumpCol->SetIsSolid(false);
		jumpCol->setPosition(0.0f, 70.0f);

		AddComponent(col);
		AddComponent(rb);
		AddComponent(jumpCol);
		AddComponent(jumpTrigger);

		m_JumpTrigger = jumpTrigger;

		AddTag(blackListedTag.GetCString());
	}

	void PlayerEntity::UpdateSelf(float dt)
	{
		if (m_Context.InputManager.IsButtonDown(m_Controller, "Right") && (m_Controller == -1 || m_Context.InputManager.AxisPosition(m_Controller, "Right") > 0.0f))
		{
			move(m_MoveSpeed * dt, 0.0f);
		}

		if (m_Context.InputManager.IsButtonDown(m_Controller, "Left") && (m_Controller == -1 || m_Context.InputManager.AxisPosition(m_Controller, "Left") < 0.0f))
		{
			move(-m_MoveSpeed * dt, 0.0f);
		}

		Collider* otherJumpCol = m_JumpTrigger->ConsumeCollision();
		if (otherJumpCol)
		{
			m_JumpCount = 2;
		}

		if (m_Context.InputManager.WasButtonPressed(m_Controller, "Jump") && m_JumpCount > 0)
		{
			--m_JumpCount;
			Collider* col = (Collider*)GetComponent("Collider");
			col->ApplyForce(sf::Vector2f(0.0f, -m_JumpStrength));
		}
	}

	void PlayerEntity::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Sprite, states);
	}
}