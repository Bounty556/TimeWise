#include "GameScene.h"

#include <ResourceManagers/TextureManager.h>

namespace Soul
{
	GameScene::GameScene(Context& context) :
		m_Player(context)
	{
		m_Player.setPosition(context.WindowWidth / 2.0f, 20.0f);
	}

	void GameScene::Update(float dt, Context& context)
	{
		m_Player.Update(dt, context);
	}

	void GameScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Player, states);
	}
}