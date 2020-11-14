#pragma once

#include <UI/UIComponent.h>
#include <Utility/Context.h>

#include <SFML/Graphics/Text.hpp>

namespace Soul
{
	class UIButton : public UIComponent
	{
	public:
		UIButton(const char* buttonText, Context& context, std::function<void()> activate);

		virtual void Update(float dt, Context& context) override;

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text m_Text;
	};
}