/*
File Name: Object.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once

#include "../../Engine/Headers/Vec2.h"
#include "../../Engine/Headers/Sprite.h"
#include "BlockImgs.h"

#include <string>

namespace Object {

	enum class Type {
		None, Block, Area, Enemy, Item, 
		Normal, Moving, OnOff, Puddle, Furry, Plant, Absorb, Spike, Button, Red, Blue,
		Wind, Water,
		Pinny, MrCloudy, Robot,
		Helium, Candy, UP_1,
		Image, 
		Count, 
		Stem, Leaf
	};

	static constexpr int BLOCK_MASK = static_cast<int>(Type::Normal);
	static constexpr int AREA_MASK = static_cast<int>(Type::Wind);
	static constexpr int ENEMY_MASK = static_cast<int>(Type::Pinny);
	static constexpr int ITEM_MASK = static_cast<int>(Type::Helium);

	class Base // parent class
	{
	protected:
		using TYPE = Object::Type; // no meaning but cool tho
		using NAME = std::string;
	public:
		Base() : pos({ 0 }), initpos({ 0 }), sprite(nullptr) {}
		Base(math::ivec2 vec) : pos(vec), initpos(vec), old_pos(vec), velocity({ 0 }), sprite(nullptr) {}
		virtual ~Base() {}
		virtual void Draw();
		virtual void Setup();
		virtual void Update(double dt);
		virtual void SetSprite(BlockImg* sprite);
		virtual std::string Info();

		virtual bool canThru() { return canthru; }
		virtual void setThru(const bool& b) { canthru = b; }
		virtual bool shouldDrawnBehind() { return false; }
		virtual bool isEnemy() { return false; }
		virtual bool isItem() { return false; }
		virtual bool isBlock() { return false; }
		virtual bool isMoving() { return false; }
		virtual bool isImage() { return false; }
		virtual bool has2ndPos() { return par_num() == 2; };
		virtual int par_num() { return 1; }
		virtual TYPE GetType() const { return TYPE::None; };
		virtual NAME GetName() const { return "BASE"; }

		math::ivec2 GetInitPos() const;
		math::vec2 GetPos() const;
		math::vec2 GetVelocity() const;
		math::vec2 GetOldPos() const;
		double GetSize() const;

		static constexpr double size = 64.0f;

	protected:

		bool can_thru = false;
		BlockImg* sprite;

		math::ivec2 initpos;
		math::vec2 pos;
		math::vec2 old_pos;
		math::vec2 velocity;

		bool canthru = false;
	};
}

#include "Block.h"
#include "Item-Enemy.h"
#include "Areas.h"