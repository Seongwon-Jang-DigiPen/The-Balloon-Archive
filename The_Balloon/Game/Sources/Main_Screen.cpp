/*
File Name: Main_Screen.cpp
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <doodle/doodle.hpp>
#include "../../Engine/Headers/Engine.h"
#include "../Headers/Main_Screen.h"
#include "../Headers/Screens.h"

Main::Main() : nextState(DOG::Input::Keyboard::Z)
, upState(DOG::Input::Keyboard::Up), downState(DOG::Input::Keyboard::Down), state_num(0), state(Main_State::Play),
developerUnlockKey1(DOG::Input::Keyboard::_1),developerUnlockKey2(DOG::Input::Keyboard::_2),developerUnlockKey3(DOG::Input::Keyboard::_3),developerUnlockKey4(DOG::Input::Keyboard::_4)
{


	for (int i = 0; i < 10; i++)
	{
		buttons.push_back(DOG::Texture{});
	}

	background.Load("assets/BACK.png");
	buttons[static_cast<int>(Main::Main_State::Play)].Load("assets/buttons/button0.png");
	buttons[static_cast<int>(Main::Main_State::Load)].Load("assets/buttons/LoadButton1.png");
	buttons[static_cast<int>(Main::Main_State::Setting)].Load("assets/buttons/button1.png");
	buttons[static_cast<int>(Main::Main_State::Credit)].Load("assets/buttons/button2.png");
	buttons[static_cast<int>(Main::Main_State::Quit)].Load("assets/buttons/button3.png");
	buttons[static_cast<int>(Main::Main_State::Play) + gap].Load("assets/buttons/button4.png");
	buttons[static_cast<int>(Main::Main_State::Load) + gap].Load("assets/buttons/LoadButton2.png");
	buttons[static_cast<int>(Main::Main_State::Setting) + gap].Load("assets/buttons/button5.png");
	buttons[static_cast<int>(Main::Main_State::Credit) + gap].Load("assets/buttons/button6.png");
	buttons[static_cast<int>(Main::Main_State::Quit) + gap].Load("assets/buttons/button7.png");
}

void Main::Load() {

	state_num = 0;
	Engine::getBackgroundSound().PlaySounds(1);
	
}

void Main::Update(double) {

	if (nextState.IsKeyPressed() == true) {

		switch (state)
		{
		case Main::Main_State::Play:
			Engine::getSaveManager().CopySaveFile();
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::CutScene0));
			break;
		case Main_State::Load:
			Engine::getSaveManager().LoadData();
			switch (Engine::getSaveManager().GetData().GetChapter())
			{
			case Chapter::CHAPTER1:
				Engine::getGSManager().SetNextState(static_cast<int>(Screens::Tutorial));
				break;
			case Chapter::CHAPTER2:
				Engine::getGSManager().SetNextState(static_cast<int>(Screens::Chapter2));
				break;
			}
			break;
		case Main::Main_State::Setting:
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::Setting));
			break;
		case Main::Main_State::Credit:
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::Credit));
			break;
		case Main::Main_State::Quit:
			Engine::getGSManager().Shutdown();
			break;
		default:
			break;
		}
	}
	UnlockdeveloperCode();
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

	state = static_cast<Main_State>(state_num);

}

void Main::Unload() {
	Engine::getBackgroundSound().Unload();
}

void Main::Draw() {
	background.Draw({ 0, 0 });

	doodle::push_settings();
	for (int i = 0; i < static_cast<int>(Main_State::Count); i++) {
		doodle::set_image_mode(doodle::RectMode::Center);
		int gap_i = i + gap;
		if (state == static_cast<Main_State>(i)) {
			buttons[gap_i].Draw({ static_cast<double>(Engine::getWindow().GetSize().x / 2),
									static_cast<double>(Engine::getWindow().GetSize().y / 2)
									- (static_cast<double>(i) * button_gap)});
		}
		else {
			buttons[i].Draw({ static_cast<double>(Engine::getWindow().GetSize().x / 2),
						static_cast<double>(Engine::getWindow().GetSize().y / 2)
						- (static_cast<double>(i * button_gap)) });
		}
	}

	if(Engine::Reference().CheckdeveloperMode() == true)
	{
		doodle::set_font_size(20);
		doodle::draw_text("Developer Mod", 100, 0);
	}
	
	doodle::pop_settings();

}

void Main::UnlockdeveloperCode()
{
	if(developerUnlockKey1.IsKeyReleased() == true)
	{
		unlockCode[0] = true;
	}
	else if (developerUnlockKey2.IsKeyReleased() == true)
	{
		if(unlockCode[0] == true)
		{
			unlockCode[1] = true;
		}
		else
		{
			unlockCode[0] = false;
		}
	}
	else if (developerUnlockKey3.IsKeyReleased() == true)
	{
		if (unlockCode[1] == true)
		{
			unlockCode[2] = true;
		}
		else
		{
			unlockCode[0] = false;
			unlockCode[1] = false;
		}
	}
	else if (developerUnlockKey4.IsKeyReleased() == true)
	{
		if (unlockCode[2] == true)
		{
			Engine::Reference().SetdeveloperMode();
		}
		else
		{
			unlockCode[0] = false;
			unlockCode[1] = false;
			unlockCode[2] = false;
		}
	}
}
