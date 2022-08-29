/* my work
File Name: Credit.cpp
Project Name: The balloon
Author(s)
Main: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <doodle/doodle.hpp>
#include "../../Engine/Headers/Engine.h"
#include "../Headers/Credit.h"
#include "../Headers/Screens.h"

Credit::Credit() : nextState(DOG::Input::Keyboard::Z)
{
}

void Credit::Load() {
	background.Load("assets/BACK.png");
	gap = 100;
	TEXT.push_back(Text({ 100,Gap() }, "President: Claude Comair"));
	TEXT.push_back(Text({ 100,Gap() }, "Instructor: KiKyeong Lim, David Ly"));
	TEXT.push_back(Text({ 100,Gap() }, "Teaching Assistant: Jina Hyun, Haewon Shon"));
	TEXT.push_back(Text({ 100,Gap() }, "Producer: Seongwon Jang"));
	TEXT.push_back(Text({ 100,Gap() }, "Technical Director: Hyunjin Kim"));
	TEXT.push_back(Text({ 100,Gap() }, "Game Designer: Sehun Kim"));
	TEXT.push_back(Text({ 100,Gap() }, "Test Manager: Sangbeom Kim"));
	gap -= 50;
	TEXT.push_back(Text({ 100,Gap() }, "Special Thanks!!!"));
	TEXT.push_back(Text({ 100,Gap() }, "MainMenu_BGM Creater: Marma"));
	TEXT.push_back(Text({ 100,Gap() }, "www.gamedevmarket.net/asset/ultimate-free-music-bundle-5353"));
	TEXT.push_back(Text({ 100,Gap() }, "Chapter1_BGM Creater: lemon42"));
	TEXT.push_back(Text({ 100,Gap() }, "www.gamedevmarket.net/asset/a-journey-awaits-867"));
	TEXT.push_back(Text({ 100,Gap() }, "Chapter2_BGM Creater: ilovepiano"));
	TEXT.push_back(Text({ 100,Gap() }, "www.gamedevmarket.net/asset/happy-quirky-complete-game-soundtrack"));
	TEXT.push_back(Text({ 100,Gap() }, "Credit_BGM Creater: inja"));
	TEXT.push_back(Text({ 100,Gap() }, "www.gamedevmarket.net/asset/ending-theme-38"));
	gap -= 50;
	TEXT.push_back(Text({ 100,Gap() }, "SFX Creater: InspectorJ"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/InspectorJ/sounds/394448"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/InspectorJ/sounds/484268"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/InspectorJ/sounds/398719"));
	TEXT.push_back(Text({ 100,Gap() }, "www.gamedevmarket.net/asset/rpg-orchestral-essentials-music-fx-free-sample"));
	TEXT.push_back(Text({ 100,Gap() }, "SFX Creater: Lefty_Studio"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/Lefty_Studios/sounds/369515"));
	TEXT.push_back(Text({ 100,Gap() }, "SFX Creater: Terhen"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/Terhen/sounds/234220"));
	TEXT.push_back(Text({ 100,Gap() }, "SFX Creater: PureAudioNinja"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/PureAudioNinja/sounds/341612/"));
	TEXT.push_back(Text({ 100,Gap() }, "SFX Creater: Mr._Fritz_"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/Mr._Fritz_/sounds/545238/"));
	TEXT.push_back(Text({ 100,Gap() }, "SFX Creater: orginaljun"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/orginaljun/sounds/157871/"));
	TEXT.push_back(Text({ 100,Gap() }, "SFX Creater: Sunejackie"));
	TEXT.push_back(Text({ 100,Gap() }, "freesound.org/people/Sunejackie/sounds/542394/"));
	TEXT.push_back(Text({ 100,Gap() }, "SFX Creater: timbeek"));
	TEXT.push_back(Text({ 100,Gap() }, "www.gamedevmarket.net/asset/casual-soundfx-pack/"));
	
	gap -= 50;
	TEXT.push_back(Text({ 100,Gap() }, "All content 2021 DigiPen (USA) Corporation, all rights reserved."));
	Engine::getBackgroundSound().PlaySounds(2);
}

void Credit::Update(double dt) {

	if (nextState.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::Main));
	}
	
	for (auto& t : TEXT)
	{
		t.Update(dt);
		if (t.position.y > Engine::getWindow().GetSize().y)
		{
			t.position.y -= TEXT.size() * 100 + Engine::getWindow().GetSize().y;
		}
	}
}

void Credit::Unload() {
	TEXT.clear();
	Engine::getBackgroundSound().Unload();
}

void Credit::Draw() {
	background.Draw({ 0, 0 });
	doodle::push_settings();
	doodle::set_fill_color(0, 100);
	doodle::draw_rectangle(0, 0, Engine::getWindow().GetSize().x, Engine::getWindow().GetSize().y);
	doodle::set_outline_width(5);
	doodle::set_font_size(20);
	doodle::set_outline_color(0);
	doodle::set_fill_color(255, 255);
	for(auto& t : TEXT)
	{
		t.draw();
	}
	doodle::pop_settings();

}
