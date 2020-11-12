#pragma once

#include <Input/InputManager.h>
#include <ResourceManagers/FontManager.h>
#include <ResourceManagers/SoundManager.h>
#include <ResourceManagers/TextureManager.h>

namespace Soul
{
	struct Context
	{
		unsigned int WindowWidth;
		unsigned int WindowHeight;

		FontManager& FontManager;
		SoundManager& SoundManager;
		TextureManager& TextureManager;
		InputManager& InputManager;
	};
}