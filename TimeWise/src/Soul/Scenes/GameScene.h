#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <Scenes/Scene.h>

namespace Soul
{
	class GameScene : public Scene
	{
	public:
		GameScene(Context& context);

		virtual void Update(float dt, Context& context) override;

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite m_Player;
	};
}