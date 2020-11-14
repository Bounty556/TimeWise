#include "UIContainer.h"

namespace Soul
{
	UIContainer::UIContainer() :
		m_Components(8),
		m_HoveredComponent(nullptr)
	{
	}

	UIContainer::~UIContainer()
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			MemoryManager::FreeMemory(m_Components[i]);
		}
	}

	void UIContainer::AddUIComponent(UIComponent* component)
	{
		if (m_Components.Length() == 0)
		{
			SelectComponent(component);
		}

		m_Components.Push(component);
	}

	void UIContainer::Update(float dt, Context& context)
	{
		if ((context.InputManager.WasButtonPressed(-1, "Select") || context.InputManager.WasButtonPressed(0, "Select")) && m_HoveredComponent)
		{
			m_HoveredComponent->Activate();
		}

		if ((context.InputManager.WasButtonPressed(-1, "Left") || (context.InputManager.WasButtonPressed(0, "Left") && context.InputManager.AxisPosition(0, "Left") < 0)) && m_HoveredComponent)
		{
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Left));
		}
		else if ((context.InputManager.WasButtonPressed(-1, "Right") || (context.InputManager.WasButtonPressed(0, "Right") && context.InputManager.AxisPosition(0, "Right") > 0)) && m_HoveredComponent)
		{
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Right));
		}
		else if ((context.InputManager.WasButtonPressed(-1, "Down") || (context.InputManager.WasButtonPressed(0, "Down") && context.InputManager.AxisPosition(0, "Down") > 0)) && m_HoveredComponent)
		{
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Down));
		}
		else if ((context.InputManager.WasButtonPressed(-1, "Up") || (context.InputManager.WasButtonPressed(0, "Up") && context.InputManager.AxisPosition(0, "Up") < 0)) && m_HoveredComponent)
		{
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Up));
		}

		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			m_Components[i]->Update(dt, context);
		}
	}

	void UIContainer::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (unsigned int i = 0; i < m_Components.Length(); ++i)
		{
			m_Components[i]->Draw(target, states);
		}
	}

	void UIContainer::SelectComponent(UIComponent* component)
	{
		if (component == nullptr)
		{
			return;
		}

		if (m_HoveredComponent)
		{
			m_HoveredComponent->SetState(UIComponent::Neutral);
		}

		component->SetState(UIComponent::Hovered);
		m_HoveredComponent = component;
	}
}