#include "MainMenuScene.h"

#include <Scenes/SceneManager.h>
#include <UI/UIButton.h>


namespace Soul
{
	MainMenuScene::MainMenuScene(Context& context) :
		m_UIContainer()
	{
		UIButton* startButton = Partition(UIButton, "Start", context, [] {});
		UIButton* quitButton = Partition(UIButton, "Quit", context, [&] { context.SceneManager.Quit(); });

		startButton->setPosition(context.WindowWidth / 2, context.WindowHeight / 2 - 20);
		quitButton->setPosition(context.WindowWidth / 2, context.WindowHeight / 2 + 20);
		startButton->AddConnection(UIComponent::Down, quitButton);

		m_UIContainer.AddUIComponent(startButton);
		m_UIContainer.AddUIComponent(quitButton);
	}

	void MainMenuScene::Update(float dt, Context& context)
	{
		m_UIContainer.Update(dt, context);
	}

	void MainMenuScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		m_UIContainer.Draw(target, states);
	}
}