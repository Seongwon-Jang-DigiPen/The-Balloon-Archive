/*
File Name: Areas.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "Objects.h"
#include "effects.h"

namespace Object {
	class Area : public Object::Base
	{
	public:
		Area() : Base(), pos2({ 0, 0 }) {}
		Area(math::ivec2 p1, math::ivec2 p2);
		void Draw() override;
		void Update(double dt) override;
		std::string Info() override;

		int par_num() override { return 2; }
		bool canThru() override { return true; }
		virtual math::ivec2 GetSecondPos() { return pos2; }

		TYPE GetType() const override { return TYPE::Area; }
		NAME GetName() const override { return "AREA"; };

	protected:
		math::ivec2 pos2;
		math::ivec2 dir;
		math::ivec2 length;
	};

	class Wind : public Area
	{
	public:
		Wind() : Area() {}
		Wind(math::ivec2 p1, math::ivec2 p2);

		void Draw() final;
		void Update(double dt) final;

		TYPE GetType() const final { return TYPE::Wind; }
		NAME GetName() const override { return "WIND"; };

		Effect::DIRECTION GetDirection() { return direction; }
		static constexpr double windPower = 300;
	private:
		Effect::DIRECTION direction = Effect::DIRECTION::Right;
		WindEffect* WE = nullptr;
	};

	class Water : public Area 
	{
	public:
		Water() : Area() {}
		Water(math::ivec2 p1, math::ivec2 p2) : Area(p1, p2) {}
		void Draw() final;
		void Update(double dt) final;

		TYPE GetType() const final { return TYPE::Water; }
		NAME GetName() const override { return "WATER"; };

	private:

	};

	class Image : public Base {
	public:
		Image() : Base() {}
		Image(math::ivec2 p1) : Base(p1) {};
		void Draw() final;
		std::string Info();
		void Update(double dt) final;
		void SetImage(DOG::Texture* tex) { texture = tex; };

		bool isImage() final { return true; };
		TYPE GetType() const final { return TYPE::Image; };
		NAME GetName() const override { return "IMAGE"; };

	private:
		DOG::Texture* texture = nullptr;
	};
}



