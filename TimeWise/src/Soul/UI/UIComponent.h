#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <Utility/Context.h>
#include <Structures/Map.h>
#include <Structures/Vector.h>

namespace Soul
{
	/*
	This class is a base UI class, which can be used to hold other UI
	components, or be inherited to have specific rendering/updating behavior.

	UI components can contain other UI components, and have a few useful
	behaviors about them. They can be in one of several states:
	Hovered,
	Disabled,
	Neutral

	And may have different behaviors/ways of being rendered for each state.

	UI components are also "linked", so moving from one UI component to
	another is automatic based on the direction the controller thumbstick
	moved, or the key on the keyboard pressed (generally left, right, up,
	down).
	
	UI can also block input to it's parents. This is done through setting a UI
	component as "capturing input".
	*/
	class UIComponent : public sf::Transformable
	{
	public:
		enum UIState
		{
			Hovered,
			Disabled,
			Neutral
		};

	public:
		UIComponent();

		virtual void HoveredUpdate(float dt, Context& context) = 0;
		
		virtual void NeutralUpdate(float dt, Context& context) = 0;

		virtual void HoveredDraw(sf::RenderTarget& target, sf::RenderStates) const = 0;

		virtual void NeutralDraw(sf::RenderTarget& target, sf::RenderStates) const = 0;

		virtual void DisabledDraw(sf::RenderTarget& target, sf::RenderStates) const = 0;

		virtual void Activate() = 0;

		void Update(float dt, Context& context);
		
		void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void SetState(UIState uiState);

		void AddConnection(const char* control, UIComponent* connectedComponent);

		bool IsCapturingInput();

	private:
		Vector<UIComponent> m_Children;
		Map<String, UIComponent*> m_Connections;
		bool m_CapturesInput;
		UIState m_UIState;
	};
}