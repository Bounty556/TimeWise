#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <Utility/String.h>

namespace Soul
{
	class ControlsMap
	{
	public:
		/*
		The current state of a button.
		*/
		enum ButtonState
		{
			Pressed,
			Released,
			Held,
			None
		};

		/*
		The origin of a button press.
		*/
		enum InputOrigin
		{
			Keyboard,
			Mouse,
			Controller
		};

		/*
		A single mapping of a control in the game to a button. This can simultaneously have a
		controller and keyboard/mouse button associated with it.
		*/
		struct Input
		{
			String InputName;
			ButtonState State;
			sf::Keyboard::Key KeyboardKey;
			sf::Mouse::Button MouseButton;
			unsigned int ControllerButton;
			float X;
			float Y;
			InputOrigin Origin;
		};

	public:
		/*
		Controls are initialized using a comma-delimited list of input names, ending with a
		semicolon.
		Ex: "Jump,Duck,Barrel Roll,Slide;"
		*/
		ControlsMap(const char* inputString, unsigned int inputs);
		~ControlsMap();

		/*
		Returns the state, origin, and X/Y info for the controls associated with the given input.
		*/
		const Input& GetInputInfo(const char* inputName) const;

		/*
		Sets the control of the given input to a button on the controller.
		*/
		void SetControllerInput(const char* input, unsigned int controllerButton);
		
		/*
		Sets the control of the given input to a button on the mouse. Overrides any existing
		keyboard input.
		*/
		void SetMouseInput(const char* input, sf::Mouse::Button mouseButton);
		
		/*
		Sets the control of the given input to a key on the keyboard. Overrides any existing
		mouse input.
		*/
		void SetKeyboardInput(const char* input, sf::Keyboard::Key keyboardKey);

	private:
		/*
		Array of Inputs that map to the games controls.
		*/
		Input* m_Controls;

		/*
		How many controls are in this map
		*/
		unsigned int m_ControlsCount;
	};
}