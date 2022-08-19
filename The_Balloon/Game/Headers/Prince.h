/*
File Name: Prince.h
Project Name: The balloon
Author(s)
Main: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include <string>
#include <doodle/color.hpp>
#include "../../Engine/Headers/Input.h"
#include "../../Engine/Headers/Vec2.h"
#include "../../Engine/Headers/Sound.h"
#include "../../Engine/Headers/Sprite.h"
#include "../../Engine/Headers/Particle.h"
#include "../../Engine/Headers/EffectManager.h"

enum class Prince_Anim {
	Prince_Idle_Anim,
	Prince_Run_Anim,
	Prince_Jump_Anim,
	Prince_Fall_Anim,
	Prince_Damaged_Anim,
	Prince_Dash_Anim,
	Prince_GetWater_Anim,
	Prince_Rubbing_Anim,
	Prince_Rubbing2_Anim,
	Prince_Fly_Anim

};

namespace Object {
	class Base;
	class Area;
	class Enemy_base;
	class Plant;
}

namespace DOG { class Camera; }

class Prince
{
protected:

public:
	bool GODMODE = false;
	EffectManager EM;

	
	Prince(math::vec2 startPos);

	enum class BALLOONSTATE
	{
		Normal,
		Flat,
		Electric,
		Water,
		Helium
	};

	enum class COLLISIONDIRECTION
	{
		Left,
		Right,
		Top,
		Bottom
	};

	void Load();
	
	void reset();
	//move
	void Move(double dt, math::vec2 airResistance = 0);

	//action
	void ActionUpdate();
	void GetAirUpdate();
	void DashUpdate();
	void sprinkleUpdate();
	//Update
	void Update(double dt, std::vector<Object::Base*>& blocks, std::vector<Object::Base*>& areas);
	void UpdatePosition(double dt);
	void UpdateInvisible(double dt);

	//CollisionCheck
	void AreaCollisionCheck(double dt, std::vector<Object::Base*>& areas);
	void CollisionCheck(double dt, std::vector<Object::Base*>& blocks);
	void ActionCollisionCheck(double dt, Object::Base*& obj);

	//CollsionHandling
	void MonsterCollision(double dt, Object::Base*& enemy);
	void ItemCollision(double dt, Object::Base*& item);
	void AreaCollision(double dt, Object::Area*& Area);
	void BlockCollision(double dt, Object::Base*& block);
	void OnPlatformUpdate(double dt, Object::Base*& block);
	void InteractOnOff(Object::Base*& block);
	void InteractFurry(Object::Base*& block);
	void InteractPlant(Object::Plant*& plant);
	void MonsterShove(Object::Base*& enemy);
	void SetIsHitted();
	void SetIsInvisible(double time);

	//Draw
	void Draw(const DOG::Camera& camera, double scale);
	void SprinkleDraw(const DOG::Camera& camera);
	//item
	void SetHelium();
	void SetCandy();
	//cheat
	void Cheat();
	void SetStateGOD(bool b);
	//animation
	void Animation(Prince_Anim ani);
	void spriteUpdate(double dt);
	//Redblue
	void SetRedBlue(bool* b) { RedBlue = b; }

	bool watchLeft = false;
	bool isHitted = false;
	bool gameEnding = false;
	bool isHitEnemy = false;
	bool isStuck = false;
	bool saveit = false;

private:
	DOG::Sprite sprite;
	DOG::Sprite sprite_Flat;
	DOG::Sprite sprite_Electric;
	DOG::Sprite sprite_Water;
	DOG::Sprite sprite_Effect;
	DOG::Sprite Z;
	DOG::Sprite Water;
	//Life Info
	//int Life;
	bool isDead = false;

	
	//Size Info
	double size = 60;
	double preSize = size;
	static constexpr double hardcodingvalue = 18;
	double hardcoding = 0;
	//Move Info
	static constexpr double xAcceleration = 1000;
	static constexpr double xDrag = 1600;
	static constexpr double descentSpeed = -512;
	static constexpr double shovePower = 200;
	//Jumpinfo
	double jumpPower{ 0 };
	double jumpTime{ 0 };
	static constexpr double jumpUpdateCycle{ 0.2 };
	//item Info
	int helium = 0;
	bool candy = false;
	//Invisible Info
	static constexpr double AfterDashInvisibleTime = 1; // you can just write 1 as a number
	static constexpr double AfterHittedInvisibleTime = 2;
	double InvisibleTime = 2;
	double InvisibleTimer{ 0 };
	bool blinked;
	bool isInvisible = false;
	//Action Info
	static constexpr double waterActionRangeMax{ 64 * 3 };
	double waterActionRange{ 0 };
	int WaterActionCount{ 3 };
	bool doAction = false;
	bool isDash = false;
	bool sprinkleAll = false;
	//collision info
	bool onPlatform = false;
	bool onFurryBlock = false;
	bool SideFurryBlock = false;
	bool nearPlantBlock = false;
	bool onMoveBlock = false;
	bool intoWater = false;
	bool intoWind = false;
	bool move = false;
	//Redblue
	bool* RedBlue = nullptr;
	bool onButton = false;
	bool onButton_2 = false;
	//
	std::vector<Particle*> particles;
	
	math::vec2 startPos;
	math::vec2 position;
	math::vec2 prePosition;
	math::vec2 velocity;

	//Key
	DOG::Input moveLeftKey;
	DOG::Input moveRightKey;
	DOG::Input moveUpKey;
	DOG::Input moveDownKey;
	DOG::Input jumpKey;
	DOG::Input actionKey;
	DOG::Input interactKey;

	DOG::Input changeNormal;
	DOG::Input changeFlat;
	DOG::Input changeElectric;
	DOG::Input changeWater;
	DOG::Input getHelium;
	DOG::Input loseHelium;
	DOG::Input InvisibleKey;
	DOG::Input GODKEY;

	class BalloonState
	{
	protected:
		math::vec2 maxVelocity{ 0 };
		math::vec2 minVelocity{ 0 };
		double jumpVelocity{ 0 };
		double HeliumjumpVelocity{ 0 };
		math::vec2 airResistance{ 0 }; //when Jump and fallMove, make resistance
		double gravity{ 0 };
		double size{ 0 };
		doodle::Color balloonColor{ 0 };
		BALLOONSTATE state = BALLOONSTATE::Normal;

	public:
		BalloonState() {}
		virtual ~BalloonState() {}
		virtual void Enter(Prince* prince) = 0;
		virtual void TestForExit(Prince* prince) = 0;
		virtual std::string GetName() = 0;
		math::vec2 GetMaxVel() { return maxVelocity; }
		math::vec2 GetMinVel() { return minVelocity; }
		math::vec2 GetAirResistance() { return airResistance; }
		double GetJumpVel() { return jumpVelocity; }
		double GetHeliumJumpVel() { return HeliumjumpVelocity; }
		double GetGravity() { return gravity; }
		double GetSize() { return size; }
		doodle::Color GetColor() { return balloonColor; }
		BALLOONSTATE GetState() { return state; }

	};
	class Balloon_Normal : public BalloonState
	{
	private:
	public:
		Balloon_Normal() : BalloonState()
		{
			maxVelocity = math::vec2{ 256,1000 };
			minVelocity = math::vec2{ -256, -256 };
			jumpVelocity = 800 * 1.5;
			HeliumjumpVelocity = 1000 * 1.5;
			airResistance = math::vec2{ 300,800 };
			gravity = 1024;
			size = 48;
			balloonColor = { 255,255,255 };
			state = BALLOONSTATE::Normal;
		}
		virtual ~Balloon_Normal() {};
		virtual void Enter(Prince* prince) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Normal"; }
	};
	class Balloon_Flat : public BalloonState
	{
	public:
		Balloon_Flat() : BalloonState()
		{
			maxVelocity = math::vec2{ 256,1000 };
			minVelocity = math::vec2{ -256,-1000 };
			jumpVelocity = 800 * 1.1;
			HeliumjumpVelocity = 1000 * 1.15;
			airResistance = math::vec2{ 400,600 };
			gravity = 1024;
			size = 20;
			balloonColor = { 155,155,155 };
			state = BALLOONSTATE::Flat;
		}
		~Balloon_Flat() {}
		virtual void Enter(Prince* prince) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Flat"; }
	};
	class Balloon_Electric : public BalloonState
	{
	public:
		Balloon_Electric() : BalloonState()
		{
			maxVelocity = math::vec2{ 256,1000 };
			minVelocity = math::vec2{ -256, -256 };
			jumpVelocity = 800 * 1.5;
			HeliumjumpVelocity = 1000 * 1.5;
			airResistance = math::vec2{ 300,800 };
			gravity = 1024;
			size = 48;
			balloonColor = { 255,255,255 };
			state = BALLOONSTATE::Electric;
		}
		virtual ~Balloon_Electric() {}
		virtual void Enter(Prince* prince) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Electric"; }
	};
	class Balloon_Water : public BalloonState
	{
	public:
		Balloon_Water() : BalloonState()
		{
			maxVelocity = math::vec2{ 196,1000 };
			minVelocity = math::vec2{ -196,-384 };
			jumpVelocity = 800 * 1;
			HeliumjumpVelocity = 1000 * 1;
			airResistance = math::vec2{ 400,600 };
			gravity = 1024;
			size = 48;
			balloonColor = { 0,0,255 };
			state = BALLOONSTATE::Water;
		}
		virtual ~Balloon_Water() {}
		virtual void Enter(Prince* prince) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Water"; }
	};
	class Balloon_Helium : public BalloonState
	{
	public:
		Balloon_Helium() : BalloonState()
		{
			maxVelocity = math::vec2{ 256,256 };
			minVelocity = math::vec2{ -256,-256 };
			jumpVelocity = 192;
			airResistance = math::vec2{ 300,600 };
			gravity = 512;
			size = 48;
			balloonColor = { 155,155,255 };
			state = BALLOONSTATE::Helium;
		}
		virtual ~Balloon_Helium() {};
		virtual void Enter(Prince* prince) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Helium"; }
	};

	void ChangeBalloon(BALLOONSTATE state);

	BalloonState* currBalloon;

	class State {
	public:
		virtual void Enter(Prince* prince) = 0;
		virtual void Update(Prince* prince, double dt) = 0;
		virtual void TestForExit(Prince* prince) = 0;
		virtual std::string GetName() = 0;
	};
	class State_Idle : public State {
	public:
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Idle"; }
	};
	class State_Running : public State {
	public:
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Running"; }
	};
	class State_Jumping : public State {
		bool finished_pressed = false;
		public:
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Jumping"; }
	};
	class State_Falling : public State {
	public:
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Falling"; }
	};
	class State_FallingFast : public State
	{
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "FallingFast"; }
	};
	class State_Flying : public State {
	public:
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Flying"; }
	};
	class State_Dash : public State {
		static constexpr math::vec2 DashSpeed{ 500,0 };
		static constexpr double actionTime{ 0.25 };
		double Timer{ 0 };
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Dash"; }
	};
	class State_GetAir : public State {
		static constexpr double actionTime{ 1.5 };
		double Timer{ 0 };
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "GetAir"; }
	};
	class State_GetWater : public State {
		static constexpr double actionTime{ 1 };
		double Timer{ 0 };
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "GetWater"; }
	};
	class State_Rubbing : public State
	{
		static constexpr double actionTime{ 1 };
		double Timer{ 0 };
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Rubbing"; }
	};
	class State_GOD : public State
	{
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "GOD"; }
	};
	class State_Sprinkle : public State
	{
		static constexpr double actionTime{ 1 };
		double Timer{ 0 };

		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Sprinkle"; }
	};
	class State_Swimming : public State {
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Swimming"; }
	};
	class State_GetDamage : public State {
		static constexpr double actionTime{ 1 };
		double Timer{ 0 };
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "GetDamage"; }
	};
	class State_Dead : public State {
		static constexpr double actionTime{ 1 };
		double Timer{ 0 };
		virtual void Enter(Prince* prince) override;
		virtual void Update(Prince* prince, double dt) override;
		virtual void TestForExit(Prince* prince) override;
		std::string GetName() override { return "Dead"; }
	};
	State_Idle stateIdle;
	State_Running stateRunning;
	State_Jumping stateJumping;
	State_Falling stateFalling;
	State_FallingFast stateFallingFast;
	State_Flying stateFlying;
	State_Swimming stateSwimming;

	State_Dash stateDash;
	State_Sprinkle stateSprinkle;
	State_GetAir stateGetAir;
	State_GetWater stateGetWater;
	State_Rubbing stateRubbing;
	
	State_GetDamage stateGetDamage;
	State_Dead stateDead;
	State_GOD stateGOD;

	void ChangeState(State* newState);
	State* currState;


public:

	math::vec2 GetPosition() const;
	math::vec2 GetStartPos() const;
	math::vec2 GetVelocity() const { return velocity; }
	double GetSize() const;
	int GetHelium() const;
	//int GetLife() const;
	bool GetGameover() const;
	bool GetIsDash() const;
	bool GetIsDead() const;
	bool CanInteract() const;
	int GetWaterActionCount() const;
	BALLOONSTATE GetBalloonState() const;
	

};