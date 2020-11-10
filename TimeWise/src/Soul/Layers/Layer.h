#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Soul
{
	/*
	An abstract layer class. Has methods to update and draw which both need to be overridden for
	each layer created.
	*/
	class Layer
	{
	public:
		Layer(bool passUpdate = true, bool passDraw = true);
		virtual ~Layer();

		/*
		Draws this layer.
		*/
		virtual void Draw(sf::RenderTarget& target, sf::RenderStates) const = 0;

		/*
		Updates this layer.
		*/
		virtual void Update(float dt) = 0;

		/*
		Returns whether layers below this layer in the LayerManager should be updated.
		*/
		bool PassUpdate();
		
		/*
		Returns whether layers below this layer in the LayerManager should be drawn.
		*/
		bool PassDraw();

	private:
		/*
		Whether layers below this layer in the LayerManager should be updated.
		*/
		bool m_PassUpdate;

		/*
		Whether layers below this layer in the LayerManager should be drawn.
		*/
		bool m_PassDraw;
	};
}