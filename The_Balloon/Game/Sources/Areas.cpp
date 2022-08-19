/*
File Name: Areas.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/Areas.h"
#include <doodle/drawing.hpp>

Object::Area::Area(math::ivec2 p1, math::ivec2 p2)
	: Base(p1), pos2(p2)
{
	if (p1.x < p2.x) dir.x = 1;
	if (p1.x > p2.x) dir.x = -1;
	if (p1.y < p2.y) dir.y = 1;
	if (p1.y > p2.y) dir.y = -1;

	length.x = std::abs(p2.x - p1.x) * dir.x;
	length.y = std::abs(p2.y - p1.y) * dir.y;
}

Object::Wind::Wind(math::ivec2 p1, math::ivec2 p2) : Area(p1, p2)
{
	if (p1.x < p2.x)
	{
		if (p1.y < p2.y)
		{
			direction = Effect::DIRECTION::Right;
			WE = new WindEffect(math::rect2{ p1,p2 }, math::rect2{ math::vec2(p1.x,p1.y),math::vec2(p1.x,p2.y) }, direction);
		}
		else
		{
			direction = Effect::DIRECTION::Down;
			WE = new WindEffect(math::rect2{ p1,p2 }, math::rect2{ math::vec2(p1.x,p1.y),math::vec2(p2.x,p1.y) }, direction);
		}
	}
	else
	{
		if (p1.y < p2.y)
		{
			direction = Effect::DIRECTION::Up;
			WE = new WindEffect(math::rect2{ p1,p2 }, math::rect2{ math::vec2(p2.x,p1.y),math::vec2(p1.x,p1.y) }, direction);
		}
		else
		{
			direction = Effect::DIRECTION::Left;
			WE = new WindEffect(math::rect2{ p1,p2 }, math::rect2{ math::vec2(p1.x,p2.y),math::vec2(p1.x,p1.y) }, direction);
		}
	}
}

std::string Object::Area::Info()
{
	return Base::Info() + std::to_string((int)pos2.x) + " " + std::to_string((int)pos2.y) + " ";
}

std::string Object::Image::Info() 
{
	return Base::Info() + texture->GetPath() + " ";
}

void Object::Area::Update(double)
{
}

void Object::Wind::Update(double dt)
{
	WE->Update(dt);
}


void Object::Water::Update(double)
{
}

void Object::Image::Update(double ) {}


void Object::Area::Draw()
{
	doodle::push_settings();
	doodle::set_fill_color(200, 200);
	doodle::draw_rectangle(pos.x, pos.y, length.x, length.y);
	doodle::pop_settings();
}

void Object::Wind::Draw()
{
	WE->Draw();
	doodle::push_settings();
	doodle::set_fill_color(163, 255, 226, 90); // pale mint
	doodle::draw_rectangle(pos.x, pos.y, length.x, length.y);
	doodle::pop_settings();
}

void Object::Water::Draw()
{
	doodle::push_settings();
	doodle::set_fill_color(28, 55, 255, 180); // blue
	doodle::draw_rectangle(pos.x, pos.y, length.x, length.y);
	doodle::pop_settings();
}

void Object::Image::Draw()
{ 
	texture->Draw(initpos);
}

