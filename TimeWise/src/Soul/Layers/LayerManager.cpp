#include "LayerManager.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	Vector<Layer*>* LayerManager::m_Layers;

	void LayerManager::Init()
	{
		m_Layers = Partition(Vector<Layer*>);
	}

	void LayerManager::PushLayer(Layer* layer)
	{
		m_Layers->Push(layer);
	}

	void LayerManager::PopLayer()
	{
		if (m_Layers->Length() > 0)
		{
			MemoryManager::FreeMemory((*m_Layers)[m_Layers->Length() - 1]);
			m_Layers->Pop();
		}
	}

	void LayerManager::ClearLayers()
	{
		while (m_Layers->Length() > 0)
		{
			MemoryManager::FreeMemory((*m_Layers)[m_Layers->Length() - 1]);
			m_Layers->Pop();
		}
	}

	bool LayerManager::HasLayers()
	{
		return m_Layers->Length() > 0;
	}

	void LayerManager::Update(float dt)
	{
		// Find the first layer that isn't passing the update
		unsigned int lowestLayer = 0;
		for (int i = m_Layers->Length() - 1; i >= 0; --i)
		{
			if (!(*m_Layers)[i]->PassUpdate())
			{
				lowestLayer = i;
				break;
			}
		}

		for (unsigned int i = lowestLayer; i < m_Layers->Length(); ++i)
		{
			(*m_Layers)[i]->Update();
		}
	}

	void LayerManager::Draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		// Find the first layer that isn't passing the update
		unsigned int lowestLayer = 0;
		for (int i = m_Layers->Length() - 1; i >= 0; --i)
		{
			if (!(*m_Layers)[i]->PassDraw())
			{
				lowestLayer = i;
				break;
			}
		}

		for (unsigned int i = lowestLayer; i < m_Layers->Length(); ++i)
		{
			(*m_Layers)[i]->Draw();
		}
	}

	void LayerManager::CleanUp()
	{
		ClearLayers();
		MemoryManager::FreeMemory(m_Layers);
	}
}