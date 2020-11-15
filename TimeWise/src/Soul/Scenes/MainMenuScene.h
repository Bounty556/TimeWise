#pragma once

#include <Scenes/Scene.h>
#include <Utility/Context.h>
#include <UI/UIContainer.h>

namespace Soul
{
	class MainMenuScene : public Scene
	{
	public:
		MainMenuScene(Context& context);

		virtual void Update(float dt, Context& context) override;

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		UIContainer m_UIContainer;
	};
}