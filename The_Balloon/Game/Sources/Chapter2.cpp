/*
File Name: Chapter2.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang, Sehun Kim, Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../../Engine/Headers/Engine.h"
#include "../Headers/Chapter2.h"
#include "../Headers/Screens.h"
#include "../Headers/GameOver.h"

#include "doodle/drawing.hpp"

#include <iostream>

Chapter2::Chapter2()
	: levelReload(DOG::Input::Keyboard::Home), shakeKey(DOG::Input::Keyboard::H), cheat_clear(DOG::Input::Keyboard::_0),
	prince({ 640,480 }), // ivec2 -> vec2 == error
	ui(&prince), enter_a((Engine::getWindow().GetSize() / 2).operator math::vec2(), 3), has_started(false), has_ended(false),
	Ending_a((Engine::getWindow().GetSize() / 2).operator math::vec2(), 3), time(0)
{}

void Chapter2::Load()
{

	has_started = false;
	has_ended = false;

	// character load here

	pause.Load();
	ui.Load();
	enter_a.Init();
	Ending_a.Init();
	//end.Load();
	map.SetChapter(2);
	map.SetMapDir(L"Chapter2");
	editor.SetCamera(&camera);
	editor.EditWith(map);
	editor.Load();
	//map = Engine::GameMap[0];


	int camera_extent = TileChunk::size_c * (int)Object::Block::size;
	math::ivec2 map_size = { camera_extent * GameMap::map_width_i, camera_extent * GameMap::map_height_i };
	camera.SetExtent({ { 0, 0 }, map_size });

	Background.Load("assets/Back/chap2.spt");
	Star.Load("assets/Back/chap2_star.spt");
	map2.Load("Assets/img_tiles/chap2.png");
	prince.SetRedBlue(map.getRedBlue());
	prince.Load();
	

	camera.SetPosition(prince.GetPosition() - math::vec2{ Engine::getWindow().GetSize().operator math::vec2() / 2 });

	editor.SetChapter(2);
	map.SetChapter(2);

	Engine::getBackgroundSound().PlaySounds(3);
}

void Chapter2::Update(double dt)
{
	if (prince.isHitEnemy == true) {
		dt /= 10;
		time += 1;
		if (time > 20) {
			prince.isHitEnemy = false;
			time = 0;
		}
	}

	math::vec2 anime_offset_pos = prince.GetPosition() - camera.GetPosition(); // need to check
	enter_a.Update(dt, anime_offset_pos);
	Ending_a.Update(dt, anime_offset_pos);
	if (has_started == false) {
		has_started = true;
		enter_a.Play();
	}

	if (shakeKey.IsKeyPressed() == true)
		dt = 0;

	// character update here

	if (pause.GetState() == false) // && end.GetEnded() == true
	{
		if (editor.IsConfigurating() == false)
			camera.Update(dt, prince.GetPosition());
		editor.Update();
		math::ivec2 ppos = { (int)prince.GetPosition().x, (int)prince.GetPosition().y };

		map.Update(dt, editor.scale_amt, editor.IsConfigurating() ? camera.Get_iPosition() : ppos);

		std::vector<Object::Base*> tiles = map.GetTiles();
		std::vector<Object::Base*> Area = map.GetAreas();

		prince.Update(dt, tiles, Area); // initial value of reference to non-const must be an lvalue
		if (editor.IsConfigurating() && prince.GODMODE == false)
		{
			prince.SetStateGOD(true);
		}
	}

	if (prince.saveit == true)
	{
		Engine::getSaveManager().Save(Chapter::CHAPTER2, prince, &map);
		prince.saveit = false;
	}
	
	if (prince.GetIsDead() && has_ended == false) {
		has_ended = true;
		enter_a.PlayReverse();
	}

	if (enter_a.IsFinished()) {
			Engine::getGSManager().Reload();
	}
	if (prince.GetPosition().y > clearY && has_ended == false || (cheat_clear.IsKeyReleased() == true && Engine::Reference().CheckdeveloperMode() == true))
	{
		has_ended = true;
		Ending_a.PlayReverse();
	}
	if (Ending_a.IsFinished())
	{
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::CutScene7));
	}

	if (levelReload.IsKeyReleased() == true)
	{
		Engine::getGSManager().Reload();
	}

	pause.Update();
	Background.Update(dt);
	Star.Update(dt);

	if (pause.GetState() == false && Engine::getBackgroundSound().GetStatus() != sf::SoundSource::Playing)
	{
		Engine::getBackgroundSound().SetPlaying();
	}
	else if (pause.GetState() == true && Engine::getBackgroundSound().GetStatus() != sf::SoundSource::Paused)
	{
		Engine::getBackgroundSound().SetPause();
	}
}

void Chapter2::Draw()
{
	//Engine::getWindow().Clear(0xFFFFFFFF);
	Engine::getWindow().Clear(0x5baadcFF);
	Star.Draw({ 0, 0 - camera.GetPosition().y / 24 }, false);
	Background.Draw({ -1250 - camera.GetPosition().x / 12, -30 - camera.GetPosition().y / 24 }, false);

	map.Draw0(editor.scale_amt, camera, editor.IsConfigurating());
	prince.Draw(camera, editor.scale_amt);
	map.Draw1(editor.scale_amt, camera, editor.IsConfigurating());

	editor.DrawDynamic();
	editor.DrawStatic();

	ui.Draw();

	// camera.DrawRange();

	if (pause.GetState() == true) {
		pause.Draw();
		map2.Draw({ 0, 0 });
	}

	//end.draw(prince, camera);
	enter_a.Draw(editor.scale_amt);
	Ending_a.Draw(editor.scale_amt);
}

void Chapter2::Unload()
{
	pause.Unload();

	Engine::getEffectSound().Unload();
	Engine::getBackgroundSound().Unload();

	map.Unload(); // I hate this :/
	editor.UnLoad();
}