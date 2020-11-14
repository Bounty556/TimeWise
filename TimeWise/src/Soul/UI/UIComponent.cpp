#include "UIComponent.h"

namespace Soul
{
	UIComponent::UIComponent(std::function<void()> activate) :
		m_UIState(UIState::Neutral),
		m_Activate(activate)
	{
		m_Connections[0] = nullptr;
		m_Connections[1] = nullptr;
		m_Connections[2] = nullptr;
		m_Connections[3] = nullptr;
	}

	void UIComponent::Update(float dt, Context& context)
	{
		
	}

	void UIComponent::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}

	void UIComponent::Activate()
	{
		m_Activate();
	}

	void UIComponent::AddConnection(UIConnection direction, UIComponent* connectedComponent)
	{
		m_Connections[(int)direction] = connectedComponent;
		connectedComponent->m_Connections[((int)direction + 2) % 4] = this;
	}

	UIComponent::UIState UIComponent::GetState() const
	{
		return m_UIState;
	}

	UIComponent* UIComponent::GetConnection(UIConnection connection) const
	{
		return m_Connections[(int)connection];
	}

	void UIComponent::SetState(UIState uiState)
	{
		m_UIState = uiState;
	}
}