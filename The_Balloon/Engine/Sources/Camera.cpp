/*
File Name: Camera.cpp
Project Name: The balloon
Author(s)
Main:Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/Engine.h"
#include "../Headers/Camera.h"
#include "doodle/drawing.hpp"
#include "doodle/random.hpp"

DOG::Camera::Camera()
	: extent({ {0, 0}, {0, 0} }), position(0, 0), shake_amt(0), shake_time(0)
{}

// get the position of camera
const math::vec2& DOG::Camera::GetPosition() const
{
	return position;
}

const math::ivec2& DOG::Camera::Get_iPosition() const
{
	return math::ivec2((int)position.x, (int)position.y);
}

// set the camera position to new position
void DOG::Camera::SetPosition(math::vec2 newPosition)
{
	position.x = newPosition.x;
	position.y = newPosition.y;

	// position = newPosition;
}

// set the area where tha camera can move
void DOG::Camera::SetExtent(math::irect2 newExtent)
{
	extent.bottomLeft = newExtent.bottomLeft;

	extent.topRight = newExtent.topRight - Engine::getWindow().GetSize();
}

void DOG::Camera::Shake(double time, double amt)
{
	shake_amt = amt;
	shake_time = time;
	pre_shaked_pos = position;
}

void DOG::Camera::Update(double dt, const math::vec2& followObjPos)
{
	math::vec2 delta = easing * (followObjPos - Engine::getWindow().GetSize() / 2 - position + 30);

	position += delta;

	if (position.x >= extent.topRight.x)
	{
		position.x = extent.topRight.x;
	}
	if (position.x <= extent.bottomLeft.x)
	{
		position.x = extent.bottomLeft.x;
	}
	if (position.y >= extent.topRight.y)
	{
		position.y = extent.topRight.y;
	}
	if (position.y <= extent.bottomLeft.y)
	{
		position.y = extent.bottomLeft.y;
	}

	double static_dt = dt * 3;
	dt2 += dt;

	if (dt2 >= static_dt) {
		dt2 = 0;
	}

	if (shake_time > 0 && shake_amt > 0)
	{
		if (dt2 == 0) {
			position.x += doodle::random(-shake_amt, shake_amt + 1);
		}

		shake_amt -= dt;
		shake_time -= dt;
		if (shake_time < 0)
			position = pre_shaked_pos;
	}
}