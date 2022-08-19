/*
File Name: Camera.h
Project Name: The balloon
Author(s)
Main:Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "Vec2.h"

namespace DOG {
	class Camera {
	public: 
		Camera();
		void SetPosition(math::vec2 newPosition);
		const math::vec2& GetPosition() const;
		const math::ivec2& Get_iPosition() const;
		void SetExtent(math::irect2 newExtent);
		void Update(double dt, const math::vec2& followObjPos);
		void Shake(double time, double amt);

	private:

		double shake_time;
		double shake_amt;
		double dt2 = 0;

		math::irect2 extent;
		math::vec2 position; 
		math::vec2 pre_shaked_pos;

		static constexpr int offset_amount = 100;
		static constexpr double easing = 0.05;
	};
}