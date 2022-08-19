/*
File Name: Item-Enermy.h
Project Name: The balloon
Author(s)
Main: Sangbeom Kim
Sub: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/Input.h"
#include "../../Engine/Headers/Vec2.h"
#include "Prince.h"
#include "Objects.h"

namespace Object {
	class Enemy_base : public Object::Base
	{
	public:
		Enemy_base() : Base(), dieKey(DOG::Input::Keyboard::Space), 
			currState(&stateIdle), stoptime(0.5), accel(100), waiting(0.5) {};
		Enemy_base(math::ivec2 pos1, math::ivec2 pos2);

		bool isEnemy() override { return true; }
		TYPE GetType() const override { return TYPE::Enemy; };
		NAME GetName() const override { return "ENEMY"; };

		virtual void Update(double dt);
		void SetCollide();
		void SetDead();

		bool IsDead();
		int par_num() override { return 2; };

		void Setup() override;
		void Draw() override;

		std::string Info() override;
		bool shouldDrawnBehind() override { return true; }
	protected:

		math::ivec2 endpos;
		math::ivec2 this_p = initpos;
		math::ivec2 alter_p = endpos;
		math::vec2 velocity;

		DOG::Input dieKey;
		DOG::Sprite sprite;
		DOG::Sprite effects;

		bool toEnd = true;
		bool toStart = false;
		bool wait = false;
		bool dead = false;
		bool collide = false;
		bool flip = false;

		double accel;
		double stoptime;
		double waiting = 0;
		double alpha = 200;

		class EnemyState {
		public:
			virtual void Enter(Enemy_base* enemy) = 0;
			virtual void Update(Enemy_base* enemy, double dt) = 0;
			virtual void TestForExit(Enemy_base* enemy) = 0;
			virtual std::string GetName() = 0;
		};
		class State_Idle : public EnemyState {
		public:
			virtual void Enter(Enemy_base* enemy) override;
			virtual void Update(Enemy_base* enemy, double dt) override;
			virtual void TestForExit(Enemy_base* enemy) override;
			virtual std::string GetName() override { return "Enemy Idle"; };
		};
		class State_Moving : public EnemyState {
		public:
			virtual void Enter(Enemy_base* enemy) override;
			virtual void Update(Enemy_base* enemy, double dt) override;
			virtual void TestForExit(Enemy_base* enemy) override;
			virtual std::string GetName() override { return "Enemy Moving"; };
		};
		class State_Dead : public EnemyState {
		public:
			virtual void Enter(Enemy_base* enemy) override;
			virtual void Update(Enemy_base* enemy, double dt) override;
			virtual void TestForExit(Enemy_base* enemy) override;
			virtual std::string GetName() override { return "Enemy Dead"; };
		};
		class State_Revive : public EnemyState {
		public:
			virtual void Enter(Enemy_base* enemy) override;
			virtual void Update(Enemy_base* enemy, double dt) override;
			virtual void TestForExit(Enemy_base* enemy) override;
			virtual std::string GetName() override { return "Enemy Revive"; };
		};
		State_Idle stateIdle;
		State_Moving stateMoving;
		State_Dead stateDead;
		State_Revive stateRevive;

		void ChangeState(EnemyState* newState);

		EnemyState* currState;
	};

	class Pinny : public Enemy_base
	{
	public:
		Pinny() : Enemy_base() {}
		Pinny(math::ivec2 pos1, math::ivec2 pos2) : Enemy_base(pos1, pos2) { sprite.Load("assets/Enemy/Pinny.spt"); };
		void Draw() final;
		TYPE GetType() const final { return TYPE::Pinny; };
		NAME GetName() const override { return "PINNY"; };

	};

	class Cloudy : public Enemy_base
	{
	public:
		Cloudy() : Enemy_base() {}
		Cloudy(math::ivec2 pos1, math::ivec2 pos2) : Enemy_base(pos1, pos2) { sprite.Load("assets/Enemy/Cloudy.spt"); };
		void Draw() final;
		TYPE GetType() const final { return TYPE::MrCloudy; };
		NAME GetName() const override { return "CLOUDY"; };

	};

	class Robot : public Enemy_base
	{
	public:
		Robot() : Enemy_base() {}
		Robot(math::ivec2 pos1, math::ivec2 pos2) : Enemy_base(pos1, pos2) { sprite.Load("assets/Enemy/Mec.spt"); effects.Load("assets/Enemy/Mec_effect.spt"); };
		void Draw() final;
		TYPE GetType() const final { return TYPE::Robot; };
		NAME GetName() const override { return "ROBOT"; };

	};


	/*======================================Item=======================================*/

	class Item : public Object::Base
	{
	public:
		Item() : Base(), was_taken(false) {}
		Item(math::ivec2 pos1) : Base(pos1), was_taken(false) {}

		void Update(double dt) override;
		void Draw() override;

		bool isItem() override { return true; }
		virtual bool wasTaken() { return was_taken; }
		virtual void Taken() { was_taken = true; }
		double move = 0;

		TYPE GetType() const override { return TYPE::Item; }
		NAME GetName() const override { return "ITEM"; };

	protected:
		bool was_taken;
	};

	class Helium : public Item
	{
	public:
		Helium() : Item() {}
		Helium(math::ivec2 pos1) : Item(pos1) {}

		void Update(double dt) final;
		void Draw() final;

		doodle::Image Helium_img{ "Assets/Item/gas.png" };

		TYPE GetType() const final { return TYPE::Helium; }
		NAME GetName() const override { return "HELIUM"; };

	};

	class Candy : public Item
	{
	public:
		Candy() : Item(), init_regen_t(2), regen_t(2) {}
		Candy(math::ivec2 pos1) : Item(pos1), init_regen_t(2), regen_t(2) {}

		void Update(double dt) final;
		void Draw() final;

		doodle::Image Candy_img{ "Assets/Item/candy.png" };

		TYPE GetType() const final { return TYPE::Candy; }
		NAME GetName() const override { return "CANDY"; };

	private:
		double regen_t, init_regen_t;
	};

	class UP1 : public Item
	{
	public:
		UP1() : Item(), init_regen_t(2), regen_t(2) {}
		UP1(math::ivec2 pos1) : Item(pos1), init_regen_t(2), regen_t(2) {}

		void Update(double dt) final;
		void Draw() final;

		doodle::Image UP_img{ "Assets/Item/1UP.png" };

		TYPE GetType() const final { return TYPE::UP_1; }
		NAME GetName() const override { return "1UP"; };

	private:
		double regen_t, init_regen_t;
		
	};
}