#pragma once

#include "Soul/Application.h"

// TODO: Rectangle Node
// TODO: Text Node
// TODO: Test LayerManager
// TODO: DebugInfo layer
// TODO: Get mouse pos InputManager
// TODO: Event queue/event processing
// TODO: Make queues work with layers
// TODO: Camera
// TODO: World Layer
// TODO: Spatial tree of some sort
// TODO: Basic character
// TODO: UI
// TODO: Volatile memory management
// TODO: Networking
// TODO: Multi-threading
// TODO: Debug memory visualizer
// TODO: Add random number gen
// TODO: We may need to change how the managers work. It might be faster to load all needed
//       textures at once, then use them as needed, as we do with the FontManager.
// TODO: Remove singletons, replace with message queue
// TODO: Replace MemoryManager pointers with handles
// TODO: Make MemoryManager shift memory down to empty blocks

class Client : public Soul::Application
{
public:
	Client()
	{

	}
};