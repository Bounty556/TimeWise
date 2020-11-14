#include "UIButton.h"

namespace Soul
{
	UIButton::UIButton(const char* buttonText, Context& context, std::function<void()> activate) :
		UIComponent(activate),
		m_Text(buttonText, *(context.FontManager.RequestFont("res/font.otf")))
	{
	}

	void UIButton::Update(float dt, Context& context)
	{
		if (m_UIState == UIComponent::Hovered)
		{
			m_Text.setFillColor(sf::Color::White);
		}
		else if (m_UIState == UIComponent::Neutral)
		{
			m_Text.setFillColor(sf::Color(150, 150, 150));
		}
	}

	void UIButton::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(m_Text, states);
	}
}