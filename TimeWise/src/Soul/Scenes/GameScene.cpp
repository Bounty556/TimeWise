#include "GameScene.h"

#include <ResourceManagers/TextureManager.h>

namespace Soul
{
	GameScene::GameScene(Context& context) :
		m_Player(*(context.TextureManager.RequestTexture("res/player.png")))
	{

	}

	void GameScene::Update(float dt, Context& context)
	{

	}

	void GameScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Player, states);
	}
}