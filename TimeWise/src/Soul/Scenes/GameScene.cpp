#include "GameScene.h"

#include <ResourceManagers/TextureManager.h>

#include <SFML/Window/Keyboard.hpp>

namespace Soul
{
	GameScene::GameScene(Context& context) :
		m_Entity1(context),
		m_Entity2(context),
		m_Entity3(context),
		m_Entity4(context),
		m_Player(context, -1),
		m_Player2(context, 0)
	{
		m_Entity1.setPosition(550.0f, 0.0f);
		m_Entity2.setPosition(550.0f, 75.0f);
		m_Entity3.setPosition(-640.0f, context.WindowHeight - 100.0f);
		m_Entity4.setPosition(560.0f, context.WindowHeight - 100.0f);
		m_Player.setPosition(700.0f, 50.0f);
		m_Player2.setPosition(750.0f, 50.0f);
		m_Entity3.SetVelocity(-0.1f, 0.0f);
		m_Entity4.SetVelocity(-0.1f, 0.0f);
	}

	void GameScene::Update(float dt, Context& context)
	{
		m_Entity1.Update(dt);
		m_Entity2.Update(dt);
		m_Entity3.Update(dt);
		m_Entity4.Update(dt);
		m_Player.Update(dt);
		m_Player2.Update(dt);
	}

	void GameScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Player, states);
		target.draw(m_Player2, states);
	}
}