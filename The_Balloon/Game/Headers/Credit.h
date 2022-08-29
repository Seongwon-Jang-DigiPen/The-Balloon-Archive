/* my work
File Name: Credit.h
Project Name: The balloon
Author(s)
Main: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/GameState.h"
#include "../../Engine/Headers/Texture.h"
#include <vector>

class Credit : public DOG::GameState {
public:

	struct Text
	{
		Text(math::vec2 p, std::string t) :position(p), text(t) {}
		math::vec2 position;
		std::string text;
		void Update(double dt)
		{
			position.y += 50 * dt;
		}
		void draw() { doodle::draw_text(text, position.x, position.y); }
	};
	
	Credit();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;
	double Gap() { gap -= 100; return gap; }
	std::string GetName() override { return "Credit"; }
private:

	constexpr static int pos_x{ 150 };

	std::vector<DOG::Texture> buttons;
	DOG::Texture background;
	DOG::Input nextState;
	double gap = 100;
	//Text President;
	//Text Instructor;
	//Text TA;
	//Text Producer;
	//Text TechnicalDirector;
	//Text GameDesigner;
	//Text TestManager;

	std::vector<Text> TEXT;
};
#pragma once
