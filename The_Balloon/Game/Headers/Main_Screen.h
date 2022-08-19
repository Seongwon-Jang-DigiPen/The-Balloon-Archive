/*
File Name: Main_Screen.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/GameState.h"
#include "../../Engine/Headers/Texture.h"
#include <vector>

class Main : public DOG::GameState {
public:

	Main();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;

	void UnlockdeveloperCode();
	
	std::string GetName() override { return "Main"; }
private:

	enum class Main_State
	{
		Play = 0,
		Load,
		Setting,
		Credit,
		Quit,
		Count
	};

	int state_num = 0;
	static constexpr int gap{ 5 };
	static constexpr double button_gap{ 80 };

	Main_State state;
	std::vector<DOG::Texture> buttons;
	DOG::Texture background;
	DOG::Input nextState;
	DOG::Input upState;
	DOG::Input downState;

	DOG::Input developerUnlockKey1;
	DOG::Input developerUnlockKey2;
	DOG::Input developerUnlockKey3;
	DOG::Input developerUnlockKey4;

	bool unlockCode[4] = {false};
	
};
