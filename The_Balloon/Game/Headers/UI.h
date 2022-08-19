/*
File Name: UI.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/GameState.h"
#include "../../Engine/Headers/Texture.h"
#include "../../Engine/Headers/Vec2.h"
#include "Prince.h"

class UI {

public:
	UI(Prince* prince_t);
	void Load();
	void Draw();
private:
	math::ivec2 Helium_xy{ 96, 650 };
	math::ivec2 Helium_Gap{ 176, 650 };

	Prince* prince;
	DOG::Texture Life;
	DOG::Texture Helium;
	DOG::Texture Helium_empty;
};