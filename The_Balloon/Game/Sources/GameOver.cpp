/*
File Name: GameOver.cpp
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../../Engine/Headers/Engine.h"
#include "../../Game/Headers/Screens.h"
#include "../Headers/GameOver.h"
#include "../../Engine/Headers/Camera.h"
#include <doodle/doodle.hpp>
#include <cmath>

GameOver::GameOver() {}

void GameOver::Load() {
	texture.Load("assets/GameOver.png");
	getTime = 0;
}
void GameOver::Update(double dt) {


	getTime += dt;
	if (getTime > limit_) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::Main));
	}
}
void GameOver::Unload() {
}

void GameOver::Draw() {

	Engine::getWindow().Clear(0x342826FF);
	texture.Draw({ (static_cast<double>(Engine::getWindow().GetSize().x) - texture.GetSize().x) / 2.0,
				   (static_cast<double>(Engine::getWindow().GetSize().y) - texture.GetSize().y) / 2.0 });
}

void Anim::Update(double dt, math::vec2 pos){
	timer -= dt; 
	position = pos;
}

void Anim::Init() {
	timer = time_std;
	isReverse = false;
	isCoveredAll = false;
}

void Anim::Draw(double scale)
{
	if (timer <= 0)
		return;

	doodle::push_settings();
	doodle::set_outline_width(10);
	doodle::set_outline_color(doodle::HexColor(0x342826FF));
	doodle::apply_scale(scale);
	doodle::no_fill();

	double t = time_std - timer;
	if (isReverse == false) {
		for (int i = 0; i < 200; i++) {
			int pixels = i * 10;
			int s = static_cast<int>(t * 1200) + i + 100 + pixels;
			doodle::draw_ellipse(position.x, position.y, s, s);
		}
	}
	else
		for (int i = 0; i < 200; i++) {
			int pixels = i * 10;
			int s = 1700 - static_cast<int>(t * 600) + pixels;
			if (s <= 0) {
				if (timer <= 0.3)
					isCoveredAll = true;
				s = 0;
				return;
			}
			doodle::draw_ellipse(position.x, position.y, s, s);
		}

	doodle::pop_settings();
}
