/*
File Name: Tutorial.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang, Sehun Kim, Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../../Engine/Headers/Engine.h"
#include "../Headers/Tutorial.h"
#include "../Headers/Screens.h"
#include "../Headers/GameOver.h"

#include "doodle/drawing.hpp"

#include <iostream>

Tutorial::Tutorial()
	: levelReload(DOG::Input::Keyboard::Home), shakeKey(DOG::Input::Keyboard::H), cheat_clear(DOG::Input::Keyboard::_0),
	prince({ 640,480 }), // ivec2 -> vec2 == error
	ui(&prince), enter_a((Engine::getWindow().GetSize() / 2).operator math::vec2(), 3), has_started(false), has_ended(false),
	Ending_a((Engine::getWindow().GetSize() / 2).operator math::vec2(), 3), time(0)
{}

void Tutorial::Load() 
{

	has_started = false;
	has_ended = false;

	// character load here
	
	pause.Load();
	ui.Load();
	enter_a.Init();
	Ending_a.Init();
	//end.Load();
	map.SetChapter(1);
	map.SetMapDir(L"Chapter1");
	editor.SetCamera(&camera);
	editor.Load();
	//map = Engine::getGameMap(0);

	editor.EditWith(map);


	int camera_extent = TileChunk::size_c * (int)Object::Block::size;
	math::ivec2 map_size = { camera_extent * GameMap::map_width_i, camera_extent * GameMap::map_height_i };
	camera.SetExtent({ { 0, 0 }, map_size });
	Background.Load("assets/Back/back.spt");
	Star.Load("assets/Back/star.spt");
	map1.Load("Assets/img_tiles/chap1.png");
	prince.SetRedBlue(map.getRedBlue());
	prince.Load();
	
	camera.SetPosition(prince.GetPosition() - math::vec2{ Engine::getWindow().GetSize().operator math::vec2() / 2 });

	editor.SetChapter(1);

	Engine::getBackgroundSound().PlaySounds(0);
}

void Tutorial::Update(double dt)
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

	if(prince.saveit == true)
	{
		Engine::getSaveManager().Save(Chapter::CHAPTER1, prince, &map);
		prince.saveit = false;
	}
	
	if (prince.GetIsDead() && has_ended == false) {
		has_ended = true;
		enter_a.PlayReverse();
	}

	if (enter_a.IsFinished()) {
			Engine::getGSManager().Reload();
	}
	
	if ((prince.GetPosition().y > clearY && has_ended == false) || cheat_clear.IsKeyReleased() == true && Engine::Reference().CheckdeveloperMode() == true)
	{
		has_ended = true;
		Ending_a.PlayReverse();
	}
	if (Ending_a.IsFinished()) 
	{
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::CutScene5));
	}
	
	
	
	if (levelReload.IsKeyReleased() == true)
	{
		Engine::getGSManager().Reload();
	}

	pause.Update();
	Background.Update(dt);
	Star.Update(dt);

	if(pause.GetState() == false && Engine::getBackgroundSound().GetStatus() != sf::SoundSource::Playing)
	{
		Engine::getBackgroundSound().SetPlaying();
	}
	else if(pause.GetState() == true && Engine::getBackgroundSound().GetStatus() != sf::SoundSource::Paused)
	{
		Engine::getBackgroundSound().SetPause();
	}
}

void Tutorial::Draw()
{
	//Engine::getWindow().Clear(0xFFFFFFFF);
	Engine::getWindow().Clear(0x212a42FF);
	Star.Draw({ 0, 400 - camera.GetPosition().y / 4 }, false);
	Background.Draw({ 0 - camera.GetPosition().x / 4, 200 - camera.GetPosition().y / 4 }, false);

	map.Draw0(editor.scale_amt, camera, editor.IsConfigurating());
	prince.Draw(camera, editor.scale_amt);
	map.Draw1(editor.scale_amt, camera, editor.IsConfigurating());

	editor.DrawDynamic();
	editor.DrawStatic();
	
	ui.Draw();

	// camera.DrawRange();

	if (pause.GetState() == true) {
		pause.Draw();
		map1.Draw({ 0, 0 });
	}

	//end.draw(prince, camera);
	enter_a.Draw(editor.scale_amt);
	Ending_a.Draw(editor.scale_amt);
}

void Tutorial::Unload() 
{
	pause.Unload();

	Engine::getEffectSound().Unload();
	Engine::getBackgroundSound().Unload();

	map.Unload(); // I hate this :/
	editor.UnLoad();
}