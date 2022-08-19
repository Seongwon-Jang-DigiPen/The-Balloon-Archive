/*
File Name: Input_doodle.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <doodle/input.hpp>
#include "../Headers/Engine.h"

DOG::Input::Keyboard DoodleToEngineKey(doodle::KeyboardButtons Key) 
{
	if (Key == doodle::KeyboardButtons::Enter) {
		return DOG::Input::Keyboard::Enter;
	}
	else if (Key == doodle::KeyboardButtons::Escape) {
		return DOG::Input::Keyboard::Esc;
	}
	else if (Key == doodle::KeyboardButtons::Space) {
		return DOG::Input::Keyboard::Space;
	}
	else if (Key == doodle::KeyboardButtons::Left) {
		return DOG::Input::Keyboard::Left;
	}
	else if (Key == doodle::KeyboardButtons::Right) {
		return DOG::Input::Keyboard::Right;
	}
	else if (Key == doodle::KeyboardButtons::Up) {
		return DOG::Input::Keyboard::Up;
	}
	else if (Key == doodle::KeyboardButtons::Down) {
		return DOG::Input::Keyboard::Down;
	}
	else if (Key >= doodle::KeyboardButtons::A && Key <= doodle::KeyboardButtons::Z) {
		int keyOffset = static_cast<int>(Key) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<DOG::Input::Keyboard>(static_cast<int>(DOG::Input::Keyboard::A) + keyOffset);
	}
	else if (Key >= doodle::KeyboardButtons::NumPad_0 && Key <= doodle::KeyboardButtons::NumPad_9) {
		int NumKeyoff = static_cast<int>(Key) - static_cast<int>(doodle::KeyboardButtons::NumPad_0);
		return static_cast<DOG::Input::Keyboard>(static_cast<int>(DOG::Input::Keyboard::N0) + NumKeyoff);
	}
	else if (Key >= doodle::KeyboardButtons::F1 && Key <= doodle::KeyboardButtons::F9) {
		int FnKeyoff = static_cast<int>(Key) - static_cast<int>(doodle::KeyboardButtons::F1);
		return static_cast<DOG::Input::Keyboard>(static_cast<int>(DOG::Input::Keyboard::F1) + FnKeyoff);
	}
	else if (Key >= doodle::KeyboardButtons::_0 && Key <= doodle::KeyboardButtons::_9) {
		int BarNumoff = static_cast<int>(Key) - static_cast<int>(doodle::KeyboardButtons::_0);
		return static_cast<DOG::Input::Keyboard>(static_cast<int>(DOG::Input::Keyboard::_0) + BarNumoff);
	}
	else if (Key == doodle::KeyboardButtons::Backspace) {
		return DOG::Input::Keyboard::BSpace;
	}
	else if (Key == doodle::KeyboardButtons::Subtract) {
		return DOG::Input::Keyboard::Subt;
	}
	else if (Key == doodle::KeyboardButtons::Multiply) {
		return DOG::Input::Keyboard::Mult;
	}
	else if (Key == doodle::KeyboardButtons::Divide) {
		return DOG::Input::Keyboard::Divd;
	}
	else if (Key == doodle::KeyboardButtons::Add) {
		return DOG::Input::Keyboard::Plus;
	}
	else if (Key == doodle::KeyboardButtons::Home) {
		return DOG::Input::Keyboard::Home;
	}
	else if (Key == doodle::KeyboardButtons::Home) {
		return DOG::Input::Keyboard::End;
	}
	else if (Key == doodle::KeyboardButtons::Tilde) {
		return DOG::Input::Keyboard::Tilde;
	}

	return DOG::Input::Keyboard::None;
}

void on_key_pressed(doodle::KeyboardButtons doodleButton) 
{
	DOG::Input::Keyboard button = DoodleToEngineKey(doodleButton);
	if (button != DOG::Input::Keyboard::None)
	{
		Engine::getLogger().LogVerbose("on_key_pressed");
		Engine::getInput().setKeyDown(button, true);
	}
}

#include <doodle/window.hpp>

void on_key_released(doodle::KeyboardButtons doodleButton)
{
	DOG::Input::Keyboard button = DoodleToEngineKey(doodleButton);
	if (button != DOG::Input::Keyboard::None)
	{
		Engine::getLogger().LogVerbose("on_key_released");
		Engine::getInput().setKeyDown(button, false);
		//Engine::getInput().Key = DOG::Input::Keyboard::None;
	}

	if (doodleButton == doodle::KeyboardButtons::End)
		Engine::getGSManager().Shutdown();
		//doodle::close_window();
}

void on_mouse_wheel(int scroll_amount) 
{  
	Engine::getInput().scroll_amount += scroll_amount; 
}