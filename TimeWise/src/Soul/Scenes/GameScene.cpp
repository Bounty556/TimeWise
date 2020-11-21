#include "GameScene.h"

#include <ResourceManagers/TextureManager.h>

#include <SFML/Window/Keyboard.hpp>

namespace Soul
{
	GameScene::GameScene(Context& context) :
		m_Entity1(context),
		m_Entity2(context),
		m_Entity3(context)
	{
		m_Entity1.setPosition(500.0f, 50.0f);
		m_Entity2.setPosition(550.0f, 100.0f);
		m_Entity3.setPosition(50.0f, context.WindowHeight - 100.0f);

		m_Entity2.SetVelocity(0.5f, 0.0f);
	}

	void GameScene::Update(float dt, Context& context)
	{
		m_Entity1.Update(dt);
		m_Entity2.Update(dt);
		m_Entity3.Update(dt);
	}

	void GameScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}
}