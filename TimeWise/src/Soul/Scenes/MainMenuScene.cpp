#include "MainMenuScene.h"

#include <Scenes/GameScene.h>
#include <Scenes/SceneManager.h>
#include <UI/UIButton.h>

namespace Soul
{
	MainMenuScene::MainMenuScene(Context& context) :
		m_UIContainer()
	{
		UIButton* startButton = Partition(UIButton, "Start", context, [&] { context.SceneManager.ChangeScenes(Partition(GameScene, context)); });
		UIButton* quitButton = Partition(UIButton, "Quit", context, [&] { context.SceneManager.Quit(); });

		startButton->setPosition(context.WindowWidth / 2.0f, context.WindowHeight / 2.0f - 20);
		quitButton->setPosition(context.WindowWidth / 2.0f, context.WindowHeight / 2.0f + 20);
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