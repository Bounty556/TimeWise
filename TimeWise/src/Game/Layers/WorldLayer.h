#pragma once

#include <Soul.h>

class WorldLayer : public Soul::Layer
{
public:
	WorldLayer();

	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};