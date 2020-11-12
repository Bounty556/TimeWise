#pragma once

#include <SFML/Graphics.hpp>
#include <Structures/Vector.h>
#include <UI/UIComponent.h>

namespace Soul
{
	class UIContainer
	{
	public:
		UIContainer();
		~UIContainer();

		void AddUIComponent(UIComponent* component);

		void Update(float dt, Context& context);
		void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		Vector<UIComponent*> m_Components;
	};
}