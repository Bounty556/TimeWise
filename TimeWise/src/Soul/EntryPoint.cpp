#include "Application.h"

// TODO: Remove components, switch to entities having bounding boxes and variables to check for
//       collisions.
// TODO: Add debug partition and free logging
// TODO: Add entity masses.
// TODO: Add jumping
// TODO: Fix random memory leak when adding jumping
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