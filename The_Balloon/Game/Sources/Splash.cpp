/*
File Name: Splash.cpp
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../../Engine/Headers/Engine.h"
#include "../../Game/Headers/Screens.h"
#include "../Headers/Splash.h"

Splash::Splash() {}

void Splash::Load() {
	texture.Load("assets/DigiPen_BLACK_1024px.png");
	Engine::getEffectSound().PlaySounds(9);
}
void Splash::Update(double dt) {
	getTime += dt;
	if (getTime > limit_) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::Main));
	}
}
void Splash::Unload() {
}

void Splash::Draw() {
	Engine::getWindow().Clear(0xFFFFFFFF);

	texture.Draw({ (static_cast<double>(Engine::getWindow().GetSize().x) - texture.GetSize().x) / 2.0,
				   (static_cast<double>(Engine::getWindow().GetSize().y) - texture.GetSize().y) / 2.0 });
}