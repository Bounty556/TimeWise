#include "TextNode.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <ResourceManagers/FontManager.h>

namespace Soul
{
	void TextNode::SetText(const char* text)
	{
		m_Text.setString(text);
	}

	void TextNode::SetColor(sf::Color color)
	{
		m_Text.setFillColor(color);
	}

	void TextNode::SetSize(unsigned int size)
	{
		m_Text.setCharacterSize(size);
	}

	void TextNode::SetFont(const char* file)
	{
		const sf::Font* font = FontManager::RequestFont(file);

		if (font)
		{
			m_Text.setFont(*font);
		}
	}

	void TextNode::DrawSelf(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(m_Text, states);
	}
}