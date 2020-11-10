#pragma once

#include <Soul.h>

class PlayerNode : public Soul::Node
{
public:
	PlayerNode();

private:
	virtual void UpdateSelf(float dt) override;
	virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite m_Sprite;

	float m_MoveSpeed;
};