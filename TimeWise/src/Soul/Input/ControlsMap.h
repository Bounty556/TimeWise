#pragma once

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <Strings/String.h>
#include <Structures/Map.h>

namespace Soul
{
	/*
	This class is used in conjunction with the Controller class to act as a layer of indirection
	that the game has with the input devices available to the player.

	Firstly, the controls need to be added to the controls map. This is done by passing a list of
	input names to the ControlsMap constructor. Ex:

	ControlsMap controls("Jump,Run,Duck,Swim;", 4);

	Then, should controller support be desired, you'll need to set the controller that this
	control map is associated with. Ex:

	controls.SetController(0); // Controllers are ordered by the order they were connected

	You can set each input option to 2 separate controls - one for controller and one for
	keyboard/mouse. This is done with the Set...Input() functions. Ex:

	controls.SetKeyboardInput("Jump", sf::Keyboard::Space);

	In the main game loop, these controls will need to be updated every frame. This is done with
	the UpdateInputInfo() function. Finally, you can check the state info for any input option
	via the GetInputInfo() function. Ex:

	if (controls.GetInputInfo("Jump").State & ControlsMap::ButtonState::Pressed)
	{
		...
	}

	if (controls.GetInputInfo("Swim").AxisPosition > 75.0f)
	{
		...
	}
	*/
	class ControlsMap
	{
	public:
		/*
		The current state of a button.
		*/
		enum ButtonState
		{
			Pressed = 1,
			Held = 2,
			Released = 4,
			None = 8
		};

		/*
		A single mapping of a control in the game to a button. This can simultaneously have a
		controller/axis and keyboard/mouse button associated with it.
		*/
		struct Input
		{
			Input();

			int KeyboardKey;
			int MouseButton;
			int ControllerButton;
			int Axis;

			ButtonState State;

			float AxisPosition;
		};

	public:
		ControlsMap();

		void AddInput(const char* controlString, Input input);

		/*
		Returns the Input info associated with the provided input name.
		*/
		const Input& GetInputInfo(const char* inputName) const;

		/*
		Updates the state and input info for all controls.
		*/
		void UpdateInputInfo();

		/*
		Sets the control of the given input to a button on the controller.
		*/
		void SetControllerInput(const char* controlString, unsigned int controllerButton);
		
		/*
		Sets the control of the given input to an axis on the controller.
		*/
		void SetControllerAxis(const char* controlString, sf::Joystick::Axis axis);

		/*
		Sets the control of the given input to a button on the mouse. Overrides any existing
		keyboard input.
		*/
		void SetMouseInput(const char* controlString, sf::Mouse::Button mouseButton);
		
		/*
		Sets the control of the given input to a key on the keyboard. Overrides any existing
		mouse input.
		*/
		void SetKeyboardInput(const char* controlString, sf::Keyboard::Key keyboardKey);

		/*
		Sets the controller that this control map is used for.
		*/
		void SetController(unsigned int controllerId);

		/*
		Removes all of the stored input mappings for this controls map.
		*/
		void ClearControls();

	private:
		/*
		Array of Inputs that map to the games controls.
		*/
		Map<String, Input> m_Controls;

		/*
		The Id of the controller that uses this control map. -1 if no associated controller.
		*/
		int m_ControllerId;
	};
}