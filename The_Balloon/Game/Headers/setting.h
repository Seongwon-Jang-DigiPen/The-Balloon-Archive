/*
File Name: Setting.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/GameState.h"
#include "../../Engine/Headers/Texture.h"
#include <vector>

class Setting : public DOG::GameState {
public:

	Setting();
	void Load() override;
	void Update(double) override;
	void Unload() override;
	void Draw() override;
	void Sound();
	void SFXSound();

	std::string GetName() override { return "Setting"; }
private:

	enum class Main_State
	{
		Sound = 0,
		SFX,
		Back,
		Count
	};

	int state_num = 0;
	
	constexpr static int gap{ 3 };
	constexpr static int pos_x{ 150 };
	int Volume;
	int sfxVolume;

	Main_State state;
	std::vector<DOG::Texture> buttons;
	DOG::Texture background;
	DOG::Input nextState;
	DOG::Input upState;
	DOG::Input downState;
	DOG::Input upVolume;
	DOG::Input downVolume;
};
#pragma once
