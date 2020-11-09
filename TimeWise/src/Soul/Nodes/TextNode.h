#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include <Nodes/Node.h>

namespace Soul
{
	class TextNode : public Node
	{
	public:
		void SetText(const char* text);
		void SetColor(sf::Color color);
		void SetSize(unsigned int size);
		void SetFont(const char* file);

	private:
		virtual void DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text m_Text;
	};
}