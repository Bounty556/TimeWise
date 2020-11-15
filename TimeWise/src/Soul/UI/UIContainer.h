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

		/*
		Adds a new UI Component to this UI Container, which will automatically be drawn and
		updated.
		*/
		void AddUIComponent(UIComponent* component);
		
		void Update(float dt, Context& context);
		
		void Draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
		/*
		Sets the provided UI Component to be the hovered component in this UI Container.
		*/
		void SelectComponent(UIComponent* component);

	private:
		Vector<UIComponent*> m_Components;
		UIComponent* m_HoveredComponent;
	};
}