#pragma once

#include <Layers/Layer.h>
#include <Nodes/RectangleNode.h>
#include <Nodes/TextNode.h>
#include <Structures/ObjectPool.h>

namespace Soul
{
	/*
	A debug layer that displays useful metadata regarding memory management and frame times.
	*/
	class DebugInfoLayer : public Layer
	{
	public:
		DebugInfoLayer();

		/*
		Draws this layer.
		*/
		virtual void Draw(sf::RenderTarget& target, sf::RenderStates) const override;

		/*
		Updates this layer.
		*/
		virtual void Update(float dt) override;

	private:
		TextNode m_PartitionedMemoryText;
		TextNode m_FreeMemoryText;
		TextNode m_FrameText;
		ObjectPool<RectangleNode> m_MemoryBlocks;
		float m_UpdateTimer;
		float m_GraphWidth;
		float m_GraphHeight;
		float m_GraphYStart;
		unsigned int m_FrameCount;
		bool m_IsDrawn;
	};
}