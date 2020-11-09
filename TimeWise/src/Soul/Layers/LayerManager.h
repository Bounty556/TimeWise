#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <Layers/Layer.h>
#include <Utility/Vector.h>

namespace Soul
{
	/*
	Manages all layers by updating, drawing, registering, and removing them as required.

	Layers can prevent layers below them from drawing or updating if they wish. The LayerManager
	stores layers as a stack, and as such can be pushed to, popped, or cleared as needed.
	*/
	class LayerManager
	{
	public:
		LayerManager() = delete;

		/*
		Partitions the required memory for this LayerManager. Must be called before using.
		*/
		static void Init();

		/*
		Adds the provided layer to the layer stack. Must already have been allocated via the
		MemoryManager.
		*/
		static void PushLayer(Layer* layer);

		/*
		Removes the top-most layer from the layer stack and frees its memory.
		*/
		static void PopLayer();

		/*
		Removes all layers from the layer stack and frees all memory.
		*/
		static void ClearLayers();

		/*
		Returns whether this LayerManager has any layers in the layer stack.
		*/
		static bool HasLayers();

		/*
		Sends and update signal to all layers stored in this LayerManager's layer stack.
		*/
		static void Update(float dt);

		/*
		Sends a draw signal to all layers stored in this LayerManager's layer stack.
		*/
		static void Draw(sf::RenderTarget& target, sf::RenderStates states);

		/*
		Frees any allocated memory this LayerManager has accumulated, as well as the memory of
		all of the Layers in this manager.
		*/
		static void CleanUp();

	private:
		static Vector<Layer*>* m_Layers;
	};
}