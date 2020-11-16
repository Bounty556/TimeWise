#pragma once

namespace Soul
{
	class DebugDrawer;
	class FontManager;
	class SoundManager;
	class TextureManager;
	class InputManager;
	class SceneManager;
	class PhysicsSystem;

	struct Context
	{
		unsigned int WindowWidth;
		unsigned int WindowHeight;

		DebugDrawer& DebugDrawer;
		FontManager& FontManager;
		SoundManager& SoundManager;
		TextureManager& TextureManager;
		InputManager& InputManager;
		SceneManager& SceneManager;
		PhysicsSystem& PhysicsSystem;
	};
}