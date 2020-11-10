#pragma once

#include <Soul.h>

#include "Layers/WorldLayer.h"

// TODO: World Layer
// TODO: Camera
// TODO: Basic character
// TODO: UI
// TODO: Spatial tree of some sort
// TODO: Volatile memory management
// TODO: Networking
// TODO: Multi-threading
// TODO: Add random number gen
// TODO: We may need to change how the managers work. It might be faster to load all needed
//       textures at once, then use them as needed, as we do with the FontManager.

class Client : public Soul::Application
{
public:
	Client()
	{
		Soul::LayerManager::PushLayer(Partition(WorldLayer));
	}
};