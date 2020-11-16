#include "Application.h"

// TODO: Add unique handles for components
// TODO: Store list of handles in entities
// TODO: Only update/draw/handle components through systems
// TODO: Add basic physics
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