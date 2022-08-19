/*
File Name: Block.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang, Sehun Kim, Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "Objects.h"
#include "BlockImgs.h"
#include "../../Engine/Headers/Sprite.h"
#include <iostream>

namespace Object {

	class Block : public Object::Base
	{
	public:
		Block() : Base() 
		{}
		Block(math::ivec2 p) : Base(p) {}
		static constexpr int block_fix = 7;

		void Draw() override;

		bool isBlock() override { return true; }
		TYPE GetType() const override { return TYPE::Block; };
		NAME GetName() const override { return "BLOCK"; };
	};

	class Normal : public Block
	{
	public:
		Normal() : Block() {}
		Normal(math::ivec2 vec, math:: ivec2 vec2) : Block(vec), number(vec2.x), stage(vec2.y) {}

		math::ivec2 number;
		int stage = 1;

		static constexpr int cloud_fix = 16;

		void SetStage(int stage);
		void Draw() final;
		std::string Info() final;
		int par_num() override { return 2; };
		TYPE GetType() const final { return TYPE::Normal; };
		NAME GetName() const override { return "NORMAL"; };
	};

	class Moving : public Block
	{
	public:
		Moving() : Block() {}
		Moving(math::ivec2 pos1, math::ivec2 pos2)
			: Block(pos1), next_pos(pos2) {}

		void Draw() override;
		virtual void Update(double dt) override;
		std::string Info() override;
		TYPE GetType() const override { return TYPE::Moving; };
		NAME GetName() const override { return "MOVING"; };

		int par_num() override { return 2; };
		bool isMoving() override { return true; };

		static constexpr double accel = 100.0f;
		
	protected:
		bool isStop = false;
		bool toStart = false;
		bool toEnd = true;
		double wait = 0.5f;

		math::ivec2 next_pos;
		math::ivec2 this_p = initpos;
		math::ivec2 alter_p = next_pos;
	};

	class OnOff : public Moving
	{
	public:
		OnOff() : Moving(), is_on(false), ON_Time(1), Timer(ON_Time) {}
		OnOff(math::ivec2 pos1, math::ivec2 pos2) : Moving(pos1, pos2), is_on(false), ON_Time(1), Timer(ON_Time) {}

		void Draw() final;
		void Update(double dt) final;
		void SetOnOff(bool value) { is_on = value; }

		TYPE GetType() const final { return TYPE::OnOff; };
		NAME GetName() const override { return "ONOFF"; };

	private:
		bool is_on;
		double ON_Time;
		double Timer;
	};

	class Furry : public Block 
	{
	public:
		Furry() : Block() {}
		Furry(math::ivec2 pos1) : Block(pos1) {}

		void Draw() final;

		TYPE GetType() const final { return TYPE::Furry; };
		NAME GetName() const override { return "FURRY"; };

	};

	class Puddle : public Block 
	{
	public:
		Puddle() : Block() {}
		Puddle(math::ivec2 pos1) : Block(pos1) {}

		void Draw() final;

		TYPE GetType() const final { return TYPE::Puddle; };
		NAME GetName() const override { return "PUDDLE"; };

	};

	class Absorber : public Block 
	{
	public:
		Absorber() : Block() {}
		Absorber(math::ivec2 pos1) : Block(pos1) {}

		void Draw() final;

		bool canThru() override { return true; }
		TYPE GetType() const final { return TYPE::Absorb; };
		NAME GetName() const override { return "ABSORBER"; };

	};

	class Plant : public Block 
	{
	public:
		Plant() : Block() {};
		Plant(math::ivec2 pos1, math::ivec2 pos2) : Block(pos1), endPos(pos2) {};
		
		std::string Info();

		void Draw() final;
		void SetGrow(bool b) { has_grow = b; };
		
		bool shouldDrawnBehind() override { return true; };
		bool canThru() override { return !has_grow; }
		bool hasGrow() { return has_grow; };
		TYPE GetType() const final { return TYPE::Plant; };
		NAME GetName() const final { return "PLANT"; };
		int par_num() override { return 2; };

		class Stem : public Block {
		public:
			Stem() : Block() {}
			Stem(Plant* origin, math::ivec2 pos1) : Block(pos1), plantPtr(origin) {}
	
			void Draw() final;
			bool shouldDrawnBehind() override { return true; };
			bool canThru() override { return true; }

			TYPE GetType() const final { return Object::Type::Stem; };
			NAME GetName() const final { return "STEM"; }
			Plant* GetOrigin() const { return plantPtr; };


		private:
			Plant* plantPtr = nullptr;

		};

		class Leaf : public Block {
		public:
			Leaf() : Block() {}
			Leaf(Plant* origin, math::ivec2 pos1) : Block(pos1), plantPtr(origin) {}

			void Draw() final;
			bool shouldDrawnBehind() override { return true; };
			bool canThru() override { return !plantPtr->hasGrow(); };

			TYPE GetType() const final { return Object::Type::Leaf; };
			NAME GetName() const final { return "LEAF"; }
			Plant* GetOrigin() const { return plantPtr; };

			void unload() { delete plantPtr; }
		private:
			Plant* plantPtr = nullptr;
		};

	private:
		bool has_grow = false;
		math::ivec2 endPos;
	};

	class Spike : public Block 
	{
	public:
		Spike() : Block() {};
		Spike(math::ivec2 pos1) : Block(pos1) {};

		void Draw() final;

		TYPE GetType() const final { return TYPE::Spike; };
		NAME GetName() const override { return "SPIKE"; };

	private:
	};

	class Button : public Block
	{
	public:
		Button() : Block() {};
		Button(math::ivec2 pos1) : Block(pos1) {};

		void Draw() final;
		bool canThru() override { return true; };
		TYPE GetType() const final { return TYPE::Button; };
		NAME GetName() const override { return "BUTTON"; };
		void SetRedblue(const bool b) { redblue = b; }
		void SetRedBlue(bool* b) {
			*b = !(*b);
			redblue = *b;
		};
		
	private:
		bool redblue = false;
		bool collied = false;
	};

	class Red : public Block
	{
	public:
		Red() : Block() {};
		Red(math::ivec2 pos1) : Block(pos1) {};

		void Draw() final;
		void SetRedblue(const bool b) { canthru = b; }

		TYPE GetType() const final { return TYPE::Red; };
		NAME GetName() const override { return "RED"; };

	private:
	};

	class Blue : public Block
	{
	public:
		Blue() : Block() {};
		Blue(math::ivec2 pos1) : Block(pos1) {};

		void Draw() final;
		void SetRedblue(const bool b) { canthru = !b; }

		TYPE GetType() const final { return TYPE::Blue; };
		NAME GetName() const override { return "BLUE"; };

	private:
	};
}

