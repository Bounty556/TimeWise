#include "GameScene.h"

#include <ResourceManagers/TextureManager.h>

namespace Soul
{
	GameScene::GameScene(Context& context) :
		m_Player(context),
		m_Stage(context)
	{
		m_Player.setPosition(context.WindowWidth / 2.0f, 20.0f);
		m_Stage.setPosition(context.WindowWidth / 2.0f, 500.0f);
	}

	void GameScene::Update(float dt, Context& context)
	{
		m_Player.Update(dt, context);
		m_Stage.Update(dt, context);
	}

	void GameScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Player, states);
		target.draw(m_Stage, states);
	}
}