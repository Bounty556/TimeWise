#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace Soul
{
	class ControlsMap
	{
	public:
		enum ButtonState
		{
			Pressed,
			Released,
			Held,
			None
		};

		enum InputOrigin
		{
			Keyboard,
			Mouse,
			Controller
		};

		struct Input
		{
			const char* InputName;
			ButtonState State;
			sf::Keyboard::Key KeyboardKey;
			sf::Mouse::Button MouseButton;
			unsigned int ControllerButton;
			float X;
			float Y;
			InputOrigin Origin;
		};

	public:
		ControlsMap(const char* inputString, unsigned int inputs);
		~ControlsMap();

		const Input& GetInputInfo(const char* inputName) const;
		void SetInputKeyboardKey(const char* input, sf::Keyboard::Key key);
		void SetInputMouseButton(const char* input, sf::Mouse::Button button);
		void SetInputControllerButton(const char* input, unsigned int button);

	private:
		Input* m_Controls;
	};
}