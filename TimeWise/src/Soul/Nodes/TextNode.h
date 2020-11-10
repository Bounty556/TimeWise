#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Nodes/Node.h>

namespace Soul
{
	/*
	A simple node that displays text to the window.
	*/
	class TextNode : public Node
	{
	public:
		/*
		Sets the string that this text node displays.
		*/
		void SetText(const char* text);

		/*
		Sets the fill color of this text node's text.
		*/
		void SetColor(sf::Color color);

		/*
		Sets the font size of this text node's text.
		*/
		void SetSize(unsigned int size);

		/*
		Sets the font of this text node's text.
		*/
		void SetFont(const char* file);

	private:
		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		/*
		The underlying sf::Text object of this Text Node.
		*/
		sf::Text m_Text;
	};
}