#include "UIContainer.h"

namespace Soul
{
	UIContainer::UIContainer() :
		m_Components(8)
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
		m_Components.Push(component);
	}

	void UIContainer::Update(float dt, Context& context)
	{
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
}