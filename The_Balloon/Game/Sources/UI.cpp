/*
File Name: UI.cpp
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <doodle/doodle.hpp>
#include "../Headers/UI.h"

UI::UI(Prince* prince_t) : prince(prince_t)
{}

void UI::Load() 
{
	Life.Load("assets/UI/Life.png");
	Helium.Load("assets/UI/gas1.png");
	Helium_empty.Load("assets/UI/gas2.png");
}

void UI::Draw()
{
	doodle::push_settings();
	doodle::set_image_mode(doodle::RectMode::Center);
	doodle::set_font_size(40);

	//Life.Draw({96, 582});
	//doodle::draw_text("x " + std::to_string(3), 164, 550); // delete it

	switch (static_cast<int>(prince->GetHelium()))
	{
	case 0:
		Helium_empty.Draw(Helium_xy);
		Helium_empty.Draw(Helium_Gap);
		break;
	case 1:
		Helium.Draw(Helium_xy);
		Helium_empty.Draw(Helium_Gap);
		break;
	case 2:
		Helium.Draw(Helium_xy);
		Helium.Draw(Helium_Gap);
		break;
	default:
		break;
	}

	//std::string state_string;

	/*switch (prince->GetBalloonState())
	{
	case Prince::BALLOONSTATE::Normal:
		state_string = "Normal";
		break;
	case Prince::BALLOONSTATE::Flat:
		state_string = "Flat";
		break;
	case Prince::BALLOONSTATE::Electric:
		state_string = "Electric";
		break;
	case Prince::BALLOONSTATE::Water:
		state_string = "Water";
		break;
	case Prince::BALLOONSTATE::Helium:
		state_string = "Helium";
		break;
	default:
		break;
	}

	doodle::draw_text(state_string, 64, 618);*/
	doodle::pop_settings();
}