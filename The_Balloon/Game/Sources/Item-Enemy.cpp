/*
File Name: Item-Enermy.cpp
Project Name: The balloon
Author(s)
Main: Sangbeom Kim
Sub: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/Item-Enemy.h"
#include "../../Engine/Headers/Engine.h"
#include "doodle/doodle.hpp"
#include <iostream>

using namespace std;

Object::Enemy_base::Enemy_base(math::ivec2 pos1, math::ivec2 pos2) :

	Base(pos1), endpos(pos2), dieKey(DOG::Input::Keyboard::D), 
	accel(200), stoptime(0), waiting(0), currState(&stateIdle)
{
	this->Setup();
}

std::string Object::Enemy_base::Info() 
{ 
	return Base::Info() + std::to_string(endpos.x) + " " + std::to_string(endpos.y) + " "; 
}

void Object::Enemy_base::Setup() {
	pos = initpos;
	toEnd = true;
	toStart = false;
	wait = false;
	dead = false;
	flip = false;
	currState = &stateIdle;
	currState->Enter(this);
}

void Object::Enemy_base::Update(double dt) {
	currState->Update(this, dt);
	currState->TestForExit(this);
	if (dieKey.IsKeyPressed() == true) {
		if (dead == false) {
			dead = true;
		}
		else if (dead == true) {
			dead = false;
		}
	}
	sprite.Update(dt);
	if (GetType() == Type::Robot) {
		effects.Update(dt);
	}
}

void Object::Enemy_base::ChangeState(EnemyState* newState) {
	currState = newState;
	currState->Enter(this);
}

void Object::Enemy_base::State_Idle::Enter(Enemy_base* enemy) {
	enemy->velocity = 0;
	enemy->wait = false;
	enemy->stoptime = doodle::random(2.0, 4.0);
	switch (enemy->GetType()) {
	case Type::Pinny:
		enemy->sprite.PlayAnimation(0);
		break;
	case Type::MrCloudy:
		enemy->sprite.PlayAnimation(0);
		break;
	case Type::Robot:
		enemy->sprite.PlayAnimation(3);
		enemy->effects.PlayAnimation(1);
		break;
	}
}

void Object::Enemy_base::State_Idle::Update(Enemy_base* enemy, double dt) {
	enemy->waiting += dt;
}

void Object::Enemy_base::State_Idle::TestForExit(Enemy_base* enemy) {
	if (enemy->waiting >= enemy->stoptime) {
		enemy->waiting = 0;
		enemy->stoptime = 0;
		enemy->ChangeState(&enemy->stateMoving);
	}
	if (enemy->dead == true) {
		enemy->ChangeState(&enemy->stateDead);
	}
}

void Object::Enemy_base::State_Moving::Enter(Enemy_base* enemy) {
	switch (enemy->GetType()) {
	case Type::Pinny:
		enemy->sprite.PlayAnimation(1);
		break;
	case Type::MrCloudy:
		enemy->sprite.PlayAnimation(0);
		break;
	case Type::Robot:
		enemy->sprite.PlayAnimation(0);
		enemy->effects.PlayAnimation(1);
		break;
	}
}

void Object::Enemy_base::State_Moving::Update(Enemy_base* enemy, double dt) {
	double angle = std::atan2(enemy->alter_p.y - enemy->pos.y, enemy->alter_p.x - enemy->pos.x);
	enemy->velocity = { std::cos(angle) * enemy->accel, std::sin(angle) * enemy->accel };
	if (enemy->alter_p.x - enemy->pos.x > 0) {
		enemy->flip = true;
	}
	else  {
		enemy->flip = false;
	}
	enemy->old_pos = enemy->pos;
	enemy->pos += enemy->velocity * dt;
	if (enemy->initpos - enemy->pos <= enemy->velocity * dt && enemy->toStart == true) {
		enemy->pos = enemy->initpos;
		enemy->wait = true;
		enemy->toStart = false;
		enemy->toEnd = true;
		enemy->this_p = enemy->initpos;
		enemy->alter_p = enemy->endpos;
	}
	else if (enemy->endpos - enemy->pos <= enemy->velocity * dt && enemy->toEnd == true) {
		enemy->pos = enemy->endpos;
		enemy->wait = true;
		enemy->toEnd = false;
		enemy->toStart = true;
		enemy->this_p = enemy->endpos;
		enemy->alter_p = enemy->initpos;
	}
}

void Object::Enemy_base::State_Moving::TestForExit(Enemy_base* enemy) {
	if (enemy->wait == true) {
		enemy->ChangeState(&enemy->stateIdle);
	}
	if (enemy->dead == true) {
		enemy->ChangeState(&enemy->stateDead);
	}
}

void Object::Enemy_base::State_Dead::Enter(Enemy_base* enemy) {
	enemy->stoptime = 5;
	switch (enemy->GetType()) {
	case Type::Pinny:
		enemy->sprite.PlayAnimation(2);
		break;
	case Type::MrCloudy:
		enemy->sprite.PlayAnimation(1);
		break;
	case Type::Robot:
		enemy->sprite.PlayAnimation(1);
		enemy->effects.PlayAnimation(0);
		break;
	}
}

void Object::Enemy_base::State_Dead::Update(Enemy_base* enemy, double dt) {
	if (enemy->alpha > 0) {
		enemy->alpha -= 5;
	}
	if (enemy->GetType() == Object::Type::Robot) {
		enemy->waiting += dt;
	}
}

void Object::Enemy_base::State_Dead::TestForExit(Enemy_base* enemy) {
	if (enemy->dead == false) {
		enemy->alpha = 200;
		enemy->ChangeState(&enemy->stateMoving);
	}
	if (enemy->GetType() == Object::Type::Robot) {
		if (enemy->waiting >= enemy->stoptime) {
			enemy->waiting = 0;
			enemy->stoptime = 0;
			enemy->ChangeState(&enemy->stateRevive);
		}
	}
}

void Object::Enemy_base::State_Revive::Enter(Enemy_base* enemy) {
	enemy->sprite.PlayAnimation(2);
	enemy->effects.PlayAnimation(1);
}

void Object::Enemy_base::State_Revive::Update(Enemy_base* enemy, double) {
	if (enemy->alpha < 200) {
		enemy->alpha += 1;
	}
}

void Object::Enemy_base::State_Revive::TestForExit(Enemy_base* enemy) {
	if (enemy->sprite.IsAnimationDone() == true) {
		enemy->ChangeState(&enemy->stateMoving);
		enemy->alpha = 200;
	}
	enemy->dead = false;
}

void Object::Enemy_base::SetCollide() {
	collide = true;
}

void Object::Enemy_base::SetDead() {
	dead = true;
}

bool Object::Enemy_base::IsDead() {
	if (dead == true) {
		return true;
	}
	return false;
}

void Object::Enemy_base::Draw() {
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_fill_color(255, 0, 0, alpha); // red
	doodle::draw_rectangle(pos.x, pos.y, size, size);
	sprite.Draw({ pos.x, pos.y }, flip);
	doodle::pop_settings();
}

void Object::Pinny::Draw() {
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_fill_color(210, 78, 78, alpha); // gray red
	//doodle::draw_rectangle(pos.x + 10, pos.y, size - 20, size - 20);
	sprite.Draw({ pos.x, pos.y }, flip);
	doodle::pop_settings();
}

void Object::Cloudy::Draw() {
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_fill_color(255, 94, 19, alpha); // orange
	//doodle::draw_rectangle(pos.x + 7, pos.y + 7, size - 14, size - 14);
	sprite.Draw({ pos.x, pos.y }, flip);
	doodle::pop_settings();
}

void Object::Robot::Draw() {
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_fill_color(161, 40, 48, alpha); // dark red
//	doodle::draw_rectangle(pos.x + 5, pos.y, size - 10, size - 10);
	sprite.Draw({ pos.x, pos.y }, flip);
	effects.Draw({ pos.x, pos.y }, flip);
	doodle::pop_settings();
}

/*======================================Item===========================================*/

void Object::Item::Update(double) {}

void Object::Helium::Update(double) { 
	move += 0.1; 
}

void Object::Candy::Update(double dt)
{
	if (was_taken == true)
	{
		regen_t -= dt;

		if (regen_t < 0) {
			was_taken = false;
			regen_t = init_regen_t;
		}
	}
	move += 0.1;
}

void Object::UP1::Update(double dt) {
	if (was_taken == true)
	{
		regen_t -= dt;

		if (regen_t < 0) {
			was_taken = false;
			regen_t = init_regen_t;
		}
	}
	move += 0.1;
}


void Object::Item::Draw()
{
	doodle::push_settings();
	doodle::set_fill_color(94, 255, 105); // lime
	doodle::draw_rectangle(pos.x, pos.y, size, size);
	doodle::pop_settings();
}


void Object::Helium::Draw()
{
	doodle::draw_image(Helium_img, pos.x, pos.y + cos(move) * 2, size, size);
}

void Object::Candy::Draw()
{
	if(!was_taken)
	doodle::draw_image(Candy_img, pos.x, pos.y + cos(move) * 2, size, size);
}

void Object::UP1::Draw()
{
	doodle::draw_image(UP_img, pos.x, pos.y + cos(move) * 2, size, size);
}