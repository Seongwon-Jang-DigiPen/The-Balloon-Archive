/*
File Name: Object.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/Objects.h"
#include "doodle/drawing.hpp"

math::vec2 Object::Base::GetPos() const { 
	switch (GetType()) {
	default:
		return pos;
		break;
	case Type::Pinny:
		return { pos.x + 10, pos.y };
		break;
	case Type::MrCloudy:
		return { pos.x + 7, pos.y + 7 };
		break;
	case Type::Robot:
		return { pos.x + 5, pos.y };
		break;
	case Type::Candy:
		return pos + 15;
		break;
	case Type::Helium:
		return pos + 15;
		break;
	case Type::UP_1:
		return pos + 15;
		break;
	}
}

double Object::Base::GetSize() const { 
	switch (GetType()) {
	default:
		return size;
		break;
	case Type::Pinny:
		return size - 20;
		break;
	case Type::MrCloudy:
		return size - 14;
		break;
	case Type::Robot:
		return size - 10;
		break;
	case Type::Candy:
		return size - 30;
		break;
	case Type::Helium:
		return size - 30;
		break;
	case Type::UP_1:
		return size - 30;
		break;
	}
}


std::string Object::Base::Info() {
	return GetName() + " " + std::to_string(static_cast<int>(GetType())) + " " 
		+ std::to_string(initpos.x) + " " + std::to_string(initpos.y) + " ";
}

math::ivec2 Object::Base::GetInitPos() const { return initpos; }
math::vec2 Object::Base::GetOldPos() const { return old_pos; }
math::vec2 Object::Base::GetVelocity() const { return velocity; }

void Object::Base::Update(double) {}
void Object::Base::SetSprite(BlockImg* sprite_) {
	sprite = sprite_;
}
void Object::Base::Setup() {}
void Object::Base::Draw() {}
