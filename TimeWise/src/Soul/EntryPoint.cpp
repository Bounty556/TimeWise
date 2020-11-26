#include "Application.h"

// TODO: Add Entity tags?
// TODO: Add Triggers
// TODO: Add jumping
// TODO: Add platform movement
// TODO: Volatile memory management
// TODO: Networking
// TODO: Multi-threading
// TODO: Add random number gen
// TODO: We may need to change how the managers work. It might be faster to load all needed
//       textures at once, then use them as needed, as we do with the FontManager.

int main()
{
	Soul::Application app;
	app.Run();
}