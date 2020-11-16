#include "GameScene.h"

#include <ResourceManagers/TextureManager.h>

namespace Soul
{
	GameScene::GameScene(Context& context) :
		m_Player(context),
		m_Platform(context, sf::Vector2f(context.WindowWidth - 300, 30))
	{
		m_Player.setPosition(context.WindowWidth / 2, 20);
		m_Platform.setPosition(150, 600);
	}

	void GameScene::Update(float dt, Context& context)
	{
		m_Player.Update(dt, context);
		m_Platform.UpdateSelf(dt, context);
	}

	void GameScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Player, states);
		target.draw(m_Platform, states);
	}
}