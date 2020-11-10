#include "PlayerNode.h"

PlayerNode::PlayerNode() :
	Soul::Node(),
	m_Sprite(),
	m_MoveSpeed(0.5f)
{
	m_Sprite.setTexture(*Soul::TextureManager::RequestTexture("res/player.png"));
}

void PlayerNode::UpdateSelf(float dt)
{
	// Movement vector
	sf::Vector2f movement;

	if (Soul::InputManager::GetControllerInputInfo(-1, "Left").State & Soul::ControlsMap::ButtonState::Held)
	{
		movement.x -= 1.0f;
	}

	if (Soul::InputManager::GetControllerInputInfo(-1, "Right").State & Soul::ControlsMap::ButtonState::Held)
	{
		movement.x += 1.0f;
	}

	if (Soul::InputManager::GetControllerInputInfo(-1, "Up").State & Soul::ControlsMap::ButtonState::Held)
	{
		movement.y -= 1.0f;
	}

	if (Soul::InputManager::GetControllerInputInfo(-1, "Down").State & Soul::ControlsMap::ButtonState::Held)
	{
		movement.y += 1.0f;
	}

	float xAxisPos = Soul::InputManager::GetControllerInputInfo(0, "Left").AxisPosition;
	if (Soul::Math::Abs(xAxisPos) > 50.0f)
	{
		movement.x = xAxisPos / 100.0f;
	}

	float yAxisPos = Soul::InputManager::GetControllerInputInfo(0, "Up").AxisPosition;
	if (Soul::Math::Abs(yAxisPos) > 50.0f)
	{
		movement.y = yAxisPos / 100.0f;
	}

	move(movement * m_MoveSpeed * dt);
}

void PlayerNode::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}