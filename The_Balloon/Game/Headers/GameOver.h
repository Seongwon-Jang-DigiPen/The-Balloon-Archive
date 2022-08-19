/*
File Name: GameOver.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/GameState.h"
#include "../../Engine/Headers/Texture.h"
#include "prince.h"
#include <vector>

class GameOver : public DOG::GameState {
public:

	GameOver();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "GameOver"; }
private:
	const double limit_{ 3 };
	double getTime{ 0 };
	DOG::Texture texture;
};

class Anim
{
public:
	Anim(math::vec2 pos, double timers)
		: position(pos), time_std(timers) {};

	void Update(double dt, math::vec2 pos);
	void Draw(double scale);
	void Init();

	void Play() {
		timer = time_std;
		isReverse = false;
	}

	void PlayReverse() {
		timer = time_std;
		isReverse = true;
	}

	bool IsFinished() { return isCoveredAll; }

private:
	math::vec2 position;
	const double time_std = 3;
	double timer = 0;

	bool isReverse = false;
	bool isCoveredAll = false;
};
