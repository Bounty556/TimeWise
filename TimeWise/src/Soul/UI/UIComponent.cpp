#include "UIComponent.h"

namespace Soul
{
	UIComponent::UIComponent() :
		m_Children(),
		m_Connections(),
		m_CapturesInput(false),
		m_UIState(UIState::Neutral)
	{

	}

	void UIComponent::Update(float dt, Context& context)
	{
		if (m_UIState == UIState::Hovered)
		{
			Vector<String*> inputs = m_Connections.GetKeys();
			for (unsigned int i = 0; i < inputs.Length(); ++i)
			{
				if (context.InputManager.WasButtonPressed(-1, inputs[i]->GetCString()) || context.InputManager.WasButtonPressed(0, inputs[i]->GetCString()))
				{
					UIComponent* connectedComponent = *m_Connections.Get(*(inputs[i]));
					if (connectedComponent->m_UIState == UIState::Neutral)
					{
						connectedComponent->SetState(UIState::Hovered);
						m_UIState = UIState::Neutral;
					}
					break;
				}
			}
		}

		switch (m_UIState)
		{
			case UIState::Hovered:
			{
				HoveredUpdate(dt, context);
			} break;

			case UIState::Neutral:
			{
				NeutralUpdate(dt, context);
			} break;
		}
	}

	void UIComponent::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		switch (m_UIState)
		{
			case UIState::Hovered:
			{
				HoveredDraw(target, states);
			} break;

			case UIState::Neutral:
			{
				NeutralDraw(target, states);
			} break;

			case UIState::Disabled:
			{
				DisabledDraw(target, states);
			} break;
		}
	}

	void UIComponent::SetState(UIState uiState)
	{
		m_UIState = uiState;
	}

	void UIComponent::AddConnection(const char* control, UIComponent* connectedComponent)
	{
		m_Connections.AddPair(control, connectedComponent);
	}

	bool UIComponent::IsCapturingInput()
	{
		return m_CapturesInput;
	}
}