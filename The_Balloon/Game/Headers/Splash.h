/*
File Name: Splash.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/GameState.h"
#include "../../Engine/Headers/Texture.h"

class Splash : public DOG::GameState {
public:
	Splash();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Splash"; }
private:
	const double limit_{ 3 };
	double getTime{ 0 };

	DOG::Texture texture;
};