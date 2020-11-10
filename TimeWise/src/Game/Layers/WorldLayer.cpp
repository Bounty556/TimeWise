#include "WorldLayer.h"

WorldLayer::WorldLayer() :
	Layer(false, false)
{
	m_Player = Partition(PlayerNode);
	m_Scene.AddChild(m_Player);
}

void WorldLayer::Update(float dt)
{
	m_Scene.Update(dt);
}

void WorldLayer::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Scene, states);
}