#pragma once

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

		/*
		Draws this layer.
		*/
		virtual void Draw() const = 0;

		/*
		Updates this layer.
		*/
		virtual void Update() const = 0;

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