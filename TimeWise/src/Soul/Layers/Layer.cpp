#include "Layer.h"

namespace Soul
{
	Layer::Layer(bool passUpdate, bool passDraw) :
		m_PassUpdate(passUpdate),
		m_PassDraw(passDraw)
	{

	}

	bool Layer::PassUpdate()
	{
		return m_PassUpdate;
	}

	bool Layer::PassDraw()
	{
		return m_PassDraw;
	}
}