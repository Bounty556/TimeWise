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

		static void Init();

		static void PushLayer(Layer* layer);

		static void PopLayer();

		static void ClearLayers();

		static bool HasLayers();

		static void Update(float dt);

		static void Draw(sf::RenderTarget& target, sf::RenderStates states);

		static void CleanUp();

	private:
		static Vector<Layer*>* m_Layers;
	};
}