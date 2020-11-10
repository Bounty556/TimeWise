#pragma once

#include <Soul.h>

#include "../Nodes/PlayerNode.h"

class WorldLayer : public Soul::Layer
{
public:
	WorldLayer();

	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Soul::Node m_Scene;
	PlayerNode* m_Player;
};