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

		virtual void Draw() const = 0;
		virtual void Update() const = 0;

		bool PassUpdate();
		bool PassDraw();

	private:
		bool m_PassUpdate;
		bool m_PassDraw;
	};
}