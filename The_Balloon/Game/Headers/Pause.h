/*
File Name: Pause.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
Sub: Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/Texture.h"

class Pause {
public:
	Pause();
	bool GetState();
	void Draw();
	void Load();
	void Unload();
	void Update();

	bool Pause_state;

private:
	enum class Main_State
	{
		Play = 0,
		Quit,
		Count
	};

	static constexpr double button_gap{ 110 };
	static constexpr int gap{ 2 };

	int state_num;

	Main_State state;
	std::vector<DOG::Texture> buttons;
	DOG::Texture pause_img;
	DOG::Input pause;
	DOG::Input select;
	DOG::Input upState;
	DOG::Input downState;
};