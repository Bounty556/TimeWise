#include "PlayerEntity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <Input/InputManager.h>
#include <ResourceManagers/TextureManager.h>

namespace Soul
{
	PlayerEntity::PlayerEntity(Context& context) :
		m_Sprite(*(context.TextureManager.RequestTexture("res/player.png"))),
		m_Gravity(this, 0.006f, 1.0f)
	{

	}

	void PlayerEntity::UpdateSelf(float dt, Context& context)
	{
		if (context.InputManager.IsButtonDown(-1, "Right"))
		{
			move(1.0f * dt, 0.0f);
		}

		if (context.InputManager.IsButtonDown(-1, "Left"))
		{
			move(-1.0f * dt, 0.0f);
		}

		if (context.InputManager.IsButtonDown(-1, "Down"))
		{
			move(0.0f, 1.0f * dt);
		}
	
		if (context.InputManager.IsButtonDown(-1, "Up"))
		{
			move(0.0, -1.0f * dt);
		}

		m_Gravity.Update(dt, context);
	}

	void PlayerEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(m_Sprite, states);
	}
}