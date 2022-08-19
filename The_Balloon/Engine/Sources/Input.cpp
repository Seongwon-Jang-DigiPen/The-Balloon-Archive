/*
File Name: Input.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include "../Headers/Engine.h"
#include "../Headers/Input.h"

#include "doodle/drawing.hpp"
#include "doodle/input.hpp"

DOG::Input::Input(Keyboard button) 
{
	this->button = button;
}

bool DOG::Input::IsKeyDown() const
{
	return Engine::getInput().IsKeyDown(button);
}

bool DOG::Input::IsKeyReleased() const 
{ 
	return Engine::getInput().IsKeyReleased(button);
}

bool DOG::Input::IsKeyPressed() const 
{
	return Engine::getInput().IsKeyPressed(button);
}

DOG::InputSystem::InputSystem()
{
	keyDown.resize(static_cast<int>(Input::Keyboard::Count));
	wasKeyDown.resize(static_cast<int>(Input::Keyboard::Count));
}

bool DOG::InputSystem::IsKeyDown(Input::Keyboard key) const 
{
	return this->keyDown[static_cast<int>(key)];
}

bool DOG::InputSystem::IsKeyReleased(Input::Keyboard key) const
{
	const int number = static_cast<int>(key); //key number
	if (this->keyDown[number] == false && this->wasKeyDown[number] == true)
	{
		return true;
	}
	return false;
}

bool DOG::InputSystem::IsKeyPressed(Input::Keyboard key) const
{
	const int number = static_cast<int>(key);
	if (this->keyDown[number] == true && this->wasKeyDown[number] == false)
	{
		return true;
	}
	return false;
}

void DOG::InputSystem::setKeyDown(Input::Keyboard key, bool value) 
{
	keyDown[static_cast<int>(key)] = value;
}

void DOG::InputSystem::Update() 
{
	wasKeyDown = keyDown;
}

math::ivec2 DOG::InputSystem::GetMousePosition()
{
	return math::ivec2{ doodle::get_mouse_x(), doodle::get_mouse_y() };
}

math::ivec2 DOG::InputSystem::GetPMousePosition()
{
	return math::ivec2( doodle::get_previous_mouse_x(), doodle::get_previous_mouse_y() );
}

math::ivec2 DOG::InputSystem::GetMouseDirection()
{
	math::ivec2 temp_ivec2 = GetMousePosition() - GetPMousePosition();
	temp_ivec2.x = std::clamp(temp_ivec2.x, -1, 1);
	temp_ivec2.y = std::clamp(temp_ivec2.y, -1, 1);

	return temp_ivec2;
}

DOG::Button::Button(math::ivec2 pos_)
	: pos(pos_), is_clicked(false) 
{}

DOG::Button::Button(math::ivec2 pos_ , std::string name)
	: pos(pos_), is_clicked(false)
{
	texture.Load("Assets/tile_button/" + name);
}

void DOG::Button::Draw() 
{
	doodle::push_settings();
	if (IsMouseAbove() == true) {
		doodle::MouseIsPressed ? doodle::set_fill_color(80) : doodle::set_fill_color(110);
	}
	else {
		doodle::set_fill_color(140);
	}
	doodle::draw_rectangle(pos.x, pos.y, size, size);
	if (texture.GetHasLoaded()) {
		texture.Draw(pos + 3);
	}
	doodle::pop_settings();
	
}

bool DOG::Button::IsPressed()
{
	if (is_clicked == false and doodle::MouseIsPressed == true)
	{
		if (IsMouseAbove() == true)
		{
			is_clicked = doodle::MouseIsPressed;
			return true;
		}
	}

	is_clicked = doodle::MouseIsPressed;

	return false;
}

bool DOG::Button::IsMouseAbove() 
{
	if (doodle::get_mouse_x() > pos.x and doodle::get_mouse_x() < pos.x + size
		and doodle::get_mouse_y() > pos.y and doodle::get_mouse_y() < pos.y + size)
	{
		return true;
	}

	return false;
}

math::ivec2 DOG::Button::GetPosition()
{
	return pos;
}

