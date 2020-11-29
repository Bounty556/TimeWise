#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Entities/PlayerEntity.h>
#include <Entities/TestEntity.h>
#include <Entities/TestEntity2.h>
#include <Scenes/Scene.h>

namespace Soul
{
	/*
	The scene of the main play area.
	*/
	class GameScene : public Scene
	{
	public:
		GameScene(Context& context);

		virtual void Update(float dt, Context& context) override;

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		TestEntity2 m_Entity3;
		TestEntity2 m_Entity4;
		PlayerEntity m_Player;
		PlayerEntity m_Player2;
		TestEntity m_Entity1;
		TestEntity m_Entity2;
	};
}