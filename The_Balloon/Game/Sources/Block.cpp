/*
File Name: Block.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang, Sehun Kim, Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/Block.h"
#include "../../Engine/Headers/Engine.h"
#include "../Headers/Screens.h"
#include <doodle/drawing.hpp>

std::string Object::Normal::Info() {
	return Base::Info() + std::to_string((int)number.x) + " 0 ";
}

std::string Object::Moving::Info() { // onoff info also derived from this
	return Base::Info() + std::to_string((int)next_pos.x) + " " + std::to_string((int)next_pos.y) + " ";
}

std::string Object::Plant::Info() {
	return Base::Info() + std::to_string((int)endPos.x) + " " + std::to_string((int)endPos.y) + " ";
}

void Object::Moving::Update(double dt)
{
	old_pos = pos;

	double angle = std::atan2(alter_p.y - this_p.y, alter_p.x - this_p.x);
	velocity = { std::cos(angle) * accel, std::sin(angle) * accel };

	if (initpos - pos <= velocity * dt && toStart == true) {
		pos = initpos;
		isStop = true;
		wait -= dt;
		if (wait <= 0) {
			toStart = false;
			toEnd = true;
			isStop = false;
			wait = 0.5f;
			this_p = initpos;
			alter_p = next_pos;
		}
	}
	else if (next_pos - pos <= velocity * dt && toEnd == true) {
		pos = next_pos;
		isStop = true;
		wait -= dt;
		if (wait <= 0) {
			toEnd = false;
			toStart = true;
			isStop = false;
			wait = 0.5f;
			this_p = next_pos;
			alter_p = initpos;
		}
	}
	if (isStop == true) {
		velocity = 0;
	}
	if (isStop == false) {
		pos += velocity * dt;
	}
}

void Object::OnOff::Update(double dt)
{
	isStop = false;
	bool interectWithElectric = Timer <= ON_Time;
	
	if (interectWithElectric)
	{
		Timer += dt;
		this_p = initpos;
		alter_p = next_pos;
	}
	else if (!interectWithElectric)
	{
		this_p = next_pos;
		alter_p = initpos;
	}
	
	if (is_on == true)
	{
	Timer = 0;
	is_on = false;
	}

	double angle = std::atan2(alter_p.y - this_p.y, alter_p.x - this_p.x);
	velocity = { std::cos(angle) * accel, std::sin(angle) * accel };

	if (initpos - pos <= velocity * dt && !interectWithElectric)
	{
		pos = initpos;
		isStop = true;
	}
	else if(next_pos - pos <= velocity * dt && interectWithElectric)
	{
		pos = next_pos;
		isStop = true;
	}
	if (isStop == true)
	{
		velocity = 0;
	}
	else if (isStop == false) 
	{
		if (!interectWithElectric)
		{
			pos += velocity * dt;
		}
		else if(interectWithElectric && Timer == 0)
		{
			pos += velocity * dt;
		}
	}
	
	
	//if (initpos - pos <= velocity * dt && toStart == true) { // ���� ���� ��ġ�ؼ� ������
	//	pos = initpos;
	//	isStop = true;
	//	wait -= dt;
	//	if (wait <= 0) {
	//		toStart = false;
	//		toEnd = true;
	//		isStop = false;
	//		wait = 0.5f;
	//		this_p = initpos;
	//		alter_p = next_pos;
	//	}
	//}
	//else if (next_pos - pos <= velocity * dt && toEnd == true) { // �� ����
	//	pos = next_pos;
	//	isStop = true;
	//	wait -= dt;
	//	if (wait <= 0) {
	//		toEnd = false;
	//		toStart = true;
	//		isStop = false;
	//		wait = 0.5f;
	//		this_p = next_pos;
	//		alter_p = initpos;
	//	}
	//}
	//if (is_on == true)
	//{
	//	Timer = 0;
	//	is_on = false;

	//}

	//
	//if (ON_Time <= Timer || isStop == true)
	//{
	//	velocity = 0;
	//}
	//else if (ON_Time >= Timer && isStop == false) {
	//	pos += velocity * dt;
	//}

}

void Object::Normal::SetStage(int stage_) {
	stage = stage_;
}

void Object::Block::Draw()
{
	doodle::push_settings();
	doodle::set_fill_color(255); // white
	doodle::draw_rectangle(pos.x, pos.y, size, size);
	doodle::pop_settings();
}

void Object::Normal::Draw()
{
	if (stage == 2) {
		doodle::draw_image(*sprite->GetImg( 24 + number.x), pos.x - cloud_fix, pos.y - cloud_fix);
	}
	else {doodle::draw_image(*sprite->GetImg(number.x), pos.x - block_fix, pos.y);}
}

void Object::Moving::Draw()
{
	doodle::draw_image(*sprite->GetImg(9), pos.x - block_fix, pos.y);
}

void Object::OnOff::Draw()
{
	is_on == true ? doodle::draw_image(*sprite->GetImg(10), pos.x - block_fix, pos.y)
		: doodle::draw_image(*sprite->GetImg(11), pos.x - block_fix, pos.y);
}

void Object::Furry::Draw()
{
	doodle::draw_image(*sprite->GetImg(12), pos.x - block_fix, pos.y);
}

void Object::Puddle::Draw()
{
	doodle::push_settings();
	doodle::set_fill_color(94, 143, 255); // light blue
	doodle::draw_rectangle(pos.x, pos.y, size, size);
	doodle::pop_settings();
}

void Object::Plant::Draw()
{
	doodle::draw_image( *sprite->GetImg(23) , pos.x - block_fix, pos.y);
}

void Object::Plant::Leaf::Draw()
{
	if (plantPtr->hasGrow() == true) {
		if (plantPtr->GetPos().x < pos.x) {
			doodle::draw_image(*sprite->GetImg(21), pos.x - block_fix, pos.y);
		}
		else { doodle::draw_image( *sprite->GetImg(22) , pos.x - block_fix, pos.y); }
	}
}

void Object::Plant::Stem::Draw()
{
	if (plantPtr->hasGrow() == true) {
		doodle::draw_image(*sprite->GetImg(20), pos.x - block_fix, pos.y);
	}
}

void Object::Absorber::Draw()
{
	doodle::push_settings();
	doodle::set_fill_color(91, 163, 151); // dark mint
	doodle::draw_rectangle(pos.x, pos.y, size, size);
	doodle::pop_settings();
}

void Object::Spike::Draw()
{
	doodle::draw_image(*sprite->GetImg(13), pos.x - block_fix, pos.y);
}

void Object::Button::Draw()
{
	doodle::draw_image(*sprite->GetImg(14 + redblue), pos.x - block_fix, pos.y);
}

void Object::Red::Draw()
{
	doodle::draw_image(*sprite->GetImg(16 + canthru), pos.x - block_fix, pos.y);
}

void Object::Blue::Draw()
{
	doodle::draw_image(*sprite->GetImg(18 + canthru), pos.x - block_fix, pos.y);
}
