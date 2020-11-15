#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <Utility/Context.h>

namespace Soul
{
	class Scene
	{
	public:
		virtual ~Scene();

		virtual void Update(float dt, Context& context) = 0;

		virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}