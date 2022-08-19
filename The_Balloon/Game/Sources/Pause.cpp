/*
File Name: Pause.cpp
Project Name: The balloon
Author(s)
Main: Sehun Kim
Sub: Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <doodle/doodle.hpp>
#include "../../Engine/Headers/Engine.h"
#include "../Headers/Screens.h"
#include "../Headers/Pause.h"


Pause::Pause() : Pause_state(false), pause(DOG::Input::Keyboard::Esc), select(DOG::Input::Keyboard::Z)
, upState(DOG::Input::Keyboard::Up), downState(DOG::Input::Keyboard::Down), state_num(0), state(Main_State::Play) 
{
	for (int i = 0; i < 4; i++)
	{
		buttons.push_back(DOG::Texture{});
	}
	pause_img.Load("Assets/buttons/Pause.png");
	buttons[static_cast<int>(Pause::Main_State::Play)].Load("Assets/buttons/button8.png");
	buttons[static_cast<int>(Pause::Main_State::Quit)].Load("Assets/buttons/button9.png");
	buttons[static_cast<int>(Pause::Main_State::Play) + gap].Load("Assets/buttons/button10.png");
	buttons[static_cast<int>(Pause::Main_State::Quit) + gap].Load("Assets/buttons/button11.png");
}

void Pause::Load() {
	state_num = 0;
	Pause_state = false;
}

void Pause::Unload() {
}

void Pause::Update()
{

	if (pause.IsKeyPressed() == true) 
	{
		if (Pause_state == false) { Pause_state = true; }
		else Pause_state = false;
	}
	if (Pause_state == true) {
		if (select.IsKeyPressed() == true) {
			Draw(); 
		}

		if (upState.IsKeyPressed() == true) {
			if (state_num > 0) {
				state_num--;
			}
		}

		if (downState.IsKeyPressed() == true) {
			if (state_num < static_cast<int>(Main_State::Quit)) {
				state_num++;
			}
		}

		if (select.IsKeyPressed() == true) {

			switch (state)
			{
			case Pause::Main_State::Play:
				Pause_state = false;
				break;
			case Pause::Main_State::Quit:
				Engine::getGSManager().SetNextState(static_cast<int>(Screens::Main));
				break;
			default:
				break;
			}
		}

	}

	state = static_cast<Main_State>(state_num);
}


void Pause::Draw()
{
	doodle::push_settings();
	doodle::set_image_mode(doodle::RectMode::Center);
	pause_img.Draw({ static_cast<double>(Engine::getWindow().GetSize().x / 2),
					 static_cast<double>(Engine::getWindow().GetSize().y * 5 / 8)});
		
	for (int i = 0; i < static_cast<int>(Main_State::Count); i++) {
		int gap_i = i + gap;
		if (state == static_cast<Main_State>(i)) {
			buttons[gap_i].Draw({ static_cast<double>(Engine::getWindow().GetSize().x / 2),
									static_cast<double>(Engine::getWindow().GetSize().y / 2)
									- (static_cast<double>(i) * button_gap) });
		}
		else {
			buttons[i].Draw({ static_cast<double>(Engine::getWindow().GetSize().x / 2),
						static_cast<double>(Engine::getWindow().GetSize().y / 2)
						- (static_cast<double>(i * button_gap)) });
		}
	}

	doodle::pop_settings();
}

bool Pause::GetState()
{
	return Pause_state;
}