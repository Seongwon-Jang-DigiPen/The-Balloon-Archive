/*
File Name: Setting.cpp
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <doodle/doodle.hpp>
#include "../../Engine/Headers/Engine.h"
#include "../Headers/Setting.h"
#include "../Headers/Screens.h"

Setting::Setting() : nextState(DOG::Input::Keyboard::Z)
, upState(DOG::Input::Keyboard::Up), downState(DOG::Input::Keyboard::Down)
, upVolume(DOG::Input::Keyboard::Right) , downVolume(DOG::Input::Keyboard::Left)
,state_num(0), state(Main_State::Sound),Volume(2), sfxVolume(5){
	for (int i = 0; i < 6; i++)
	{
		buttons.push_back(DOG::Texture{});
	}

	background.Load("assets/BACK.png");
	buttons[static_cast<int>(Setting::Main_State::Sound)].Load("assets/buttons/BGM1.png");
	buttons[static_cast<int>(Setting::Main_State::SFX)].Load("assets/buttons/SFX1.png");
	buttons[static_cast<int>(Setting::Main_State::Back)].Load("assets/buttons/Back.png");
	buttons[static_cast<int>(Setting::Main_State::Sound) + gap].Load("assets/buttons/BGM2.png");
	buttons[static_cast<int>(Setting::Main_State::SFX) + gap].Load("assets/buttons/SFX2.png");
	buttons[static_cast<int>(Setting::Main_State::Back) + gap].Load("assets/buttons/Back2.png");

}

void Setting::Load() {

	state = Main_State::Sound;
	state_num = 0;
}

void Setting::Update(double) {

	if ((nextState.IsKeyReleased() == true )) {

		switch (state)
		{
		case Setting::Main_State::Sound:
		case Setting::Main_State::SFX:
			break;

		case Setting::Main_State::Back:
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::Main));
			break;
		default:
			break;
		}
	}

	if (state == Main_State::Sound) {
		Sound();
	}
	else if(state == Main_State::SFX)
	{
		SFXSound();
	}

	
	if (upState.IsKeyPressed() == true) {
		if (state_num > 0) {
			state_num--;
		}
	}

	if (downState.IsKeyPressed() == true) {
		if (state_num < static_cast<int>(Main_State::Back)) {
			state_num++;
		}
	}

	state = static_cast<Main_State>(state_num);
}

void Setting::Unload() {
}

void Setting::Draw() {
	background.Draw({ 0, 0 });
	doodle::push_settings();
	doodle::set_outline_width(5);
	doodle::set_outline_color(0);
	doodle::set_fill_color(100,100);
	doodle::draw_rectangle(100, 75, 1080, 570 );
	doodle::pop_settings();

	doodle::push_settings();


	if (state == Main_State::Sound) {
		buttons[static_cast<int>(Setting::Main_State::Sound) + gap].Draw({ pos_x, static_cast<double>(Engine::getWindow().GetSize().y * 2 / 3) });
	}
	else {
		buttons[static_cast<int>(Setting::Main_State::Sound)].Draw({ pos_x, static_cast<double>(Engine::getWindow().GetSize().y * 2 / 3) });
	}

	if (state == Main_State::SFX) {
		buttons[static_cast<int>(Setting::Main_State::SFX) + gap].Draw({ pos_x, static_cast<double>(Engine::getWindow().GetSize().y / 3) });
	}
	else {
		buttons[static_cast<int>(Setting::Main_State::SFX)].Draw({ pos_x, static_cast<double>(Engine::getWindow().GetSize().y / 3) });
	}
	
	if (state == Main_State::Back) {
		buttons[static_cast<int>(Setting::Main_State::Back) + gap].Draw({ pos_x, static_cast<double>(Engine::getWindow().GetSize().y / 10) });
	}
	else {
		buttons[static_cast<int>(Setting::Main_State::Back)].Draw({ pos_x, static_cast<double>(Engine::getWindow().GetSize().y / 10) });
	}

	for (int i = 0; i < Volume; i++) 
	{
		doodle::draw_rectangle(static_cast<double>(Engine::getWindow().GetSize().x / 3) + static_cast<double>(i) * 50, Engine::getWindow().GetSize().y * 2 / 3 , 40, 80);
	}

	for (int i = 0; i < sfxVolume; i++)
	{
		doodle::draw_rectangle(static_cast<double>(Engine::getWindow().GetSize().x / 3) + static_cast<double>(i) * 50, Engine::getWindow().GetSize().y / 3, 40, 80);
	}

	doodle::pop_settings();
}

void Setting::Sound() {

	if (upVolume.IsKeyPressed() == true && Volume < 10) {
		Volume++;
		Engine::getBackgroundSound().SetSound(Volume * 10);
	}

	if (downVolume.IsKeyPressed() == true && Volume > 0) {
		Volume--;
		Engine::getBackgroundSound().SetSound(Volume * 10);
	}

}

void Setting::SFXSound() {

	if (upVolume.IsKeyPressed() == true && sfxVolume < 10) {
		sfxVolume++;
		Engine::getEffectSound().SetSound(sfxVolume * 10);
	}

	if (downVolume.IsKeyPressed() == true && sfxVolume > 0) {
		sfxVolume--;
		Engine::getEffectSound().SetSound(sfxVolume * 10);
	}

}