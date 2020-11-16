#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Entities/PlayerEntity.h>
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
		PlayerEntity m_Player;
	};
}