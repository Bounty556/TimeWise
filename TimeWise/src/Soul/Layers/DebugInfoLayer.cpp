#include "DebugInfoLayer.h"

#include <Strings/String.h>
#include <Utility/Math.h>

namespace Soul
{
	DebugInfoLayer::DebugInfoLayer() :
		Layer(true, true),
		m_UpdateTimer(5000.0f),
		m_GraphWidth(512.0f)
	{
		
		m_PartitionedMemoryText.SetFont("res/font.otf");
		m_PartitionedMemoryText.SetSize(14);
		m_FreeMemoryText.SetFont("res/font.otf");
		m_FreeMemoryText.SetSize(14);
		m_FreeMemoryText.setPosition(0.0f, 16.0f);
	}

	DebugInfoLayer::~DebugInfoLayer()
	{
		for (unsigned int i = 0; i < m_MemoryBlocks.Length(); ++i)
		{
			MemoryManager::FreeMemory(m_MemoryBlocks[i]);
		}
	}

	void DebugInfoLayer::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_PartitionedMemoryText, states);
		target.draw(m_FreeMemoryText, states);

		for (unsigned int i = 0; i < m_MemoryBlocks.Length(); ++i)
		{
			target.draw(*(m_MemoryBlocks[i]), states);
		}
	}

	void DebugInfoLayer::Update(float dt)
	{
		m_UpdateTimer += dt;

		if (m_UpdateTimer >= 5000.0f)
		{
			m_UpdateTimer -= 5000.0f;

			// Update text

			String partitionedMemory("Partitioned memory: ");
			partitionedMemory += String::IntToString(MemoryManager::GetTotalPartitionedMemory());
			partitionedMemory += " bytes";
			String freeMemory("Free memory: ");
			freeMemory += String::IntToString(MemoryManager::GetTotalFreeMemory());
			freeMemory += " bytes";

			m_PartitionedMemoryText.SetText(partitionedMemory.GetCString());
			m_FreeMemoryText.SetText(freeMemory.GetCString());

			// Update graph

			while (m_MemoryBlocks.Length() > 0)
			{
				MemoryManager::FreeMemory(m_MemoryBlocks[m_MemoryBlocks.Length() - 1]);
				m_MemoryBlocks.Pop();
			}

			unsigned int totalMemory = (unsigned int)MemoryManager::m_StableMemoryEnd - (unsigned int)MemoryManager::m_StableMemoryStart;

			MemoryManager::MemoryNode* currentNode = (MemoryManager::MemoryNode*)MemoryManager::m_StableMemoryStart;

			while (currentNode)
			{
				// Add free memory block
				float xPos = (float)ByteDistance(MemoryManager::m_StableMemoryStart, currentNode) / (float)totalMemory * m_GraphWidth;
				float width = (float)currentNode->BlockSize / (float)totalMemory * m_GraphWidth;

				RectangleNode* node = Partition(RectangleNode, width, 128, sf::Color::Blue);
				node->setPosition(xPos, 30.0f);

				m_MemoryBlocks.Push(node);

				// Add used memory block
				if (currentNode->BlockSize > 0)
				{
					xPos = (float)ByteDistance(MemoryManager::m_StableMemoryStart, (unsigned char*)currentNode + currentNode->BlockSize) / (float)totalMemory * m_GraphWidth;

					if (currentNode->NextNode)
					{
						unsigned int usedBytes = (unsigned int)currentNode->NextNode - (unsigned int)((unsigned char*)currentNode + currentNode->BlockSize);
						width = (float)usedBytes / (float)totalMemory * m_GraphWidth;
					}
					else
					{
						unsigned int usedBytes = (unsigned int)MemoryManager::m_StableMemoryEnd - (unsigned int)((unsigned char*)currentNode + currentNode->BlockSize);

						width = (float)usedBytes / (float)totalMemory * m_GraphWidth;
					}

					node = Partition(RectangleNode, width, 128, sf::Color::Red);
					node->setPosition(xPos, 30.0f);

					m_MemoryBlocks.Push(node);
				}

				currentNode = currentNode->NextNode;
			}
		}
	}
}