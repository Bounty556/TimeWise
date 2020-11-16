#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <Components/Component.h>

namespace Soul
{
	class RectangleComponent : public Component
	{
	public:
		RectangleComponent(Entity* entity, sf::Vector2f size);

		virtual void Update(float dt, Context& context) override;

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual const char* GetType() const override;

	private:
		sf::RectangleShape m_Rect;
	};
}