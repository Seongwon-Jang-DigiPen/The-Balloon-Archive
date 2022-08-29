/* my work
File Name: Prince.cpp
Project Name: The balloon
Author(s)
Main: Seongwon Jang
Sub: Sehun Kim, Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/Prince.h"

#include <map>

#include "../../Engine/Headers/Engine.h"
#include "doodle/doodle.hpp"
#include "../Headers/MapEditor.h"
#include "../../Engine/Headers/Camera.h"
#include "../Headers/Item-Enemy.h"
#include "../Headers/Screens.h"
#include <iostream>

Prince::Prince(math::vec2 startPos) :
	startPos(startPos),
	helium(0),
	moveLeftKey(DOG::Input::Keyboard::Left),
	moveRightKey(DOG::Input::Keyboard::Right),
	moveDownKey(DOG::Input::Keyboard::Down),
	interactKey(DOG::Input::Keyboard::Z),
	actionKey(DOG::Input::Keyboard::X),
	jumpKey(DOG::Input::Keyboard::C),
	changeNormal(DOG::Input::Keyboard::F1),
	changeFlat(DOG::Input::Keyboard::F2),
	changeElectric(DOG::Input::Keyboard::F3),
	changeWater(DOG::Input::Keyboard::F4),
	getHelium(DOG::Input::Keyboard::Q),
	loseHelium(DOG::Input::Keyboard::W),
	currBalloon(new Balloon_Normal),
	InvisibleKey(DOG::Input::Keyboard::S),
	moveUpKey(DOG::Input::Keyboard::Up),
	GODKEY(DOG::Input::Keyboard::G),
	currState(&stateIdle),
	isHitEnemy(false),
	RedBlue(nullptr)
{}

inline bool CollisionChecker(const math::vec2& ALeftBottom, const math::vec2& ARightTop, const math::vec2& BLeftBottom, const math::vec2& BRightTop)
{
	if (ARightTop.x < BLeftBottom.x || ALeftBottom.x > BRightTop.x) return false;
	if (ARightTop.y < BLeftBottom.y || ALeftBottom.y > BRightTop.y) return false;
	return true;
}

inline bool CollisionChecker(const math::vec2& a, const double& a_size, const math::vec2& b, const double& b_size)
{
	const math::vec2 ARightTop = a + a_size;
	const math::vec2 ALeftBottom = a;
	const math::vec2 BRightTop = b + b_size;
	const math::vec2 BLeftBottom = b;

	return CollisionChecker(ALeftBottom, ARightTop, BLeftBottom, BRightTop);
}

inline bool CollisionChecker(const Object::Base*& a, const Object::Base*& b)
{
	const math::vec2 ARightTop = a->GetPos() + a->GetSize();
	const math::vec2 ALeftBottom = a->GetPos();
	const math::vec2 BRightTop = b->GetPos() + b->GetSize();
	const math::vec2 BLeftBottom = b->GetPos();

	return CollisionChecker(ALeftBottom, ARightTop, BLeftBottom, BRightTop);
}

inline bool CollisionChecker(const math::vec2& ALeftBottom, const math::vec2& ARightTop, Object::Base*& b)
{
	const math::vec2 BRightTop = b->GetPos() + b->GetSize();
	const math::vec2 BLeftBottom = b->GetPos();

	return CollisionChecker(ALeftBottom, ARightTop, BLeftBottom, BRightTop);
}

inline bool CollisionChecker(const Prince& p, Object::Area*& area)
{
	const math::vec2 ARightTop = p.GetPosition() + p.GetSize();
	const math::vec2 ALeftBottom = p.GetPosition();

	math::rect2 B{ area->GetPos() ,  area->GetSecondPos() };


	return CollisionChecker(ALeftBottom, ARightTop, { B.Left(),B.Bottom() }, { B.Right(),B.Top() });
}


void Prince::Load()
{

	sprite.Load("assets/Prince/Normal.spt");
	sprite_Flat.Load("assets/Prince/Flat.spt");
	sprite_Electric.Load("assets/Prince/Electric.spt");
	sprite_Water.Load("assets/Prince/Water.spt");
	sprite_Effect.Load("assets/Prince/Effect.spt");
	Z.Load("assets/UI/Z.spt");
	Water.Load("assets/UI/Water.spt");

	//load sprite
	candy = false;
	blinked = false;
	isInvisible = false;
	GODMODE = false;
	gameEnding = false;
	isDead = false;
	isStuck = false;
	isHitted = false;
	saveit = false;
	position = startPos;
	velocity = math::vec2{ 0,0 };
	ChangeState(&stateIdle);
	//ChangeBalloon(BALLOONSTATE::Normal);
	//currState->Enter(this);
	doAction = false; 
	onButton = false;
	auto data = Engine::getSaveManager().GetData();

	*RedBlue = data.GetRedBlue();
	helium = data.GetHelium();
	position = data.GetPosition();
	ChangeBalloon(data.Getstate());
	if (helium == 2 && GetBalloonState() == BALLOONSTATE::Helium)
	{
		ChangeState(&stateFlying);
	}
}

void Prince::reset()
{
//	Life = 3;
	startPos = { 640,480 };
	doAction = false;
	isDead = false;
	helium = 0;
}


void Prince::ActionUpdate()
{
	if (doAction == false && isDead == false && isHitted == false)
	{
		if (actionKey.IsKeyPressed() == true)
		{
			switch (GetBalloonState())
			{
			case BALLOONSTATE::Flat:
				GetAirUpdate();
				break;

			case BALLOONSTATE::Normal:
				DashUpdate();
				break;

			case BALLOONSTATE::Water:
				sprinkleUpdate();
				break;
			}
		}
		else if(GetBalloonState() == BALLOONSTATE::Water && interactKey.IsKeyPressed() == true)
		{
			sprinkleAll = true;
			sprinkleUpdate();
		}
	}
	
}
void Prince::GetAirUpdate()
{
	if (onPlatform)
	{
		doAction = true;
		ChangeState(&stateGetAir);
	}
}
void Prince::DashUpdate()
{
	doAction = true;
	ChangeState(&stateDash);
}

void Prince::sprinkleUpdate()
{
	if (onPlatform)
	{
		doAction = true;
		ChangeState(&stateSprinkle);
	}
}


void Prince::Update(double dt, std::vector<Object::Base*>& blocks, std::vector<Object::Base*>& areas)
{

	if (Engine::Reference().CheckdeveloperMode() == true)
	{
		Cheat();
	}
	
	currState->Update(this, dt);
	ActionUpdate();
	UpdateInvisible(dt);

	if(GetPosition().y < 0)
	{
		isDead = true;
	}	
	Move(dt);
	if(isInvisible == true)
	{
		blinked = !blinked;
	}
	else
	{
		blinked = false;
	}
	if (GODMODE == false)
	{
		AreaCollisionCheck(dt, areas);
	}
	UpdatePosition(dt);

	if (GODMODE == false)
	{
		CollisionCheck(dt, blocks);
	}
	EM.UpdateAll(dt);

	spriteUpdate(dt);
	
	currState->TestForExit(this);
	currBalloon->TestForExit(this);

	if (CanInteract() == true) { 
		Z.Update(dt);
	}
}


void Prince::Move(double dt, math::vec2 airResistance)
{
	move = false;
	if (moveLeftKey.IsKeyDown() == true && !doAction && !isDead) {

		watchLeft = true;
		move = true;

		velocity.x -= (xAcceleration - airResistance.x) * dt;

		if (0 < velocity.x)
		{
			velocity.x -= xDrag * dt;
		}
		else if (currBalloon->GetMinVel().x > velocity.x)
		{
			velocity.x = currBalloon->GetMinVel().x;
		}
	}
	if (moveRightKey.IsKeyDown() == true && !doAction && !isDead) {
		watchLeft = false;
		move = true;

		velocity.x += (xAcceleration - airResistance.x) * dt;

		if (0 > velocity.x)
		{
			velocity.x += xDrag * dt;
		}
		else if (currBalloon->GetMaxVel().x < velocity.x)
		{
			velocity.x = currBalloon->GetMaxVel().x;
		}
	}
	if (move == false && isDash == false)
	{
		if (0 > velocity.x) {
			if (velocity.x > -xDrag * dt) {
				velocity.x = 0;
			}
			else {
				velocity.x += xDrag * dt;
			}
		}
		if (0 < velocity.x)
		{
			if (velocity.x < xDrag * dt) {
				velocity.x = 0;
			}
			else {
				velocity.x -= xDrag * dt;
			}
		}
	}
}



void Prince::Draw(const DOG::Camera& cam, double scale)
{
	

	doodle::push_settings();
	doodle::apply_translate(-cam.Get_iPosition().x, -cam.Get_iPosition().y);
	doodle::apply_scale(scale, scale);

	if (CanInteract() == true) {
		Z.Draw({ position.x + Z.GetFrameSize().x/4 , position.y + size }, false);
	}
	if (blinked == false)
	{
		switch (currBalloon->GetState())
		{
		case BALLOONSTATE::Normal:
		case BALLOONSTATE::Helium:
			sprite.Draw({ position.x - 4, position.y }, watchLeft);
			break;
		case BALLOONSTATE::Flat:
			sprite_Flat.Draw({ position.x - 20 + hardcoding, position.y }, watchLeft);
			break;
		case BALLOONSTATE::Electric:
			sprite_Electric.Draw({ position.x - 4, position.y }, watchLeft);
			sprite_Effect.Draw({ position.x - 4, position.y }, false);
			break;
		case BALLOONSTATE::Water:
			Water.Draw({ position.x - 4, position.y }, WaterActionCount);
			sprite_Water.Draw({ position.x - 4, position.y }, watchLeft);
			break;
		default:
			break;
		}
	}
	//doodle::set_fill_color(255, 255, 255, 100);
	//doodle::draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
	//BlinkEffect(cam, scale);
	EM.DrawAll(cam, scale);

}


void Prince::SprinkleDraw(const DOG::Camera& camera)
{
	if (doAction && GetBalloonState() == BALLOONSTATE::Water)
	{
		if (watchLeft)
		{
			doodle::draw_rectangle(position.x - waterActionRange - camera.GetPosition().x, position.y - camera.GetPosition().y, waterActionRange, size);
		}
		else
		{
			doodle::draw_rectangle(position.x + size - camera.GetPosition().x, position.y - camera.GetPosition().y, waterActionRange, size);
		}
	}
}


void Prince::UpdatePosition(double dt)
{
	if (dt < 0.2)
	{
		position += velocity * dt;
	}
}

void Prince::UpdateInvisible(double dt)
{
	if (isInvisible == true)
	{
		InvisibleTimer += dt;
		if (InvisibleTimer >= InvisibleTime)
		{
			isInvisible = false;
			InvisibleTimer = 0;
		}
	}
}

void Prince::AreaCollisionCheck(double dt, std::vector<Object::Base*>& areas)
{
	intoWater = false;
	intoWind = false;
	for (Object::Base* area : areas)
	{
		Object::Area* a = static_cast<Object::Area*>(area);
		if (CollisionChecker(*this, a))
		{
			AreaCollision(dt, a);
		}
	}
}

void Prince::CollisionCheck(double dt, std::vector<Object::Base*>& blocks)
{
	onPlatform = false;
	onFurryBlock = false;
	SideFurryBlock = false;
	onMoveBlock = false;
	bool wasCollied = onButton;
	onButton = false;

	for (Object::Base*& block : blocks)
	{
		if(onMoveBlock && block->GetType() == Object::Type::Moving)
		{
			continue;
		}
		if (doAction == true && GetBalloonState() == BALLOONSTATE::Water)
		{
			ActionCollisionCheck(dt, block);
		}
		if (block->GetType() == Object::Type::Plant) 
		{
			Object::Plant* p = static_cast<Object::Plant*>(block);
			InteractPlant(p);
		}
		if (CollisionChecker(position, this->size, block->GetPos(), block->GetSize()))
		{

			if (block->isEnemy() == true)
			{
				MonsterCollision(dt, block);
			}
			else if (block->isItem() == true)
			{
				ItemCollision(dt, block);
			}
			else if (block->GetType() == Object::Type::Absorb)
			{
				if (this->currBalloon->GetState() == BALLOONSTATE::Electric)
				{
					ChangeBalloon(BALLOONSTATE::Normal);
				}
			}
			else if (block->canThru() == false)
			{
				BlockCollision(dt, block);
			}
			else if (block->GetType() == Object::Type::Button)
			{
				Object::Button* button = static_cast<Object::Button*>(block);
				if (wasCollied == false)
				{
					button->SetRedBlue(RedBlue);	
				}
				onButton = true;
			}
		}
	}
}

void Prince::ActionCollisionCheck(double, Object::Base*& obj)
{
	if (obj->GetType() == Object::Type::Robot)
	{
		Object::Enemy_base* enemy = (Object::Enemy_base*)obj;

		if (watchLeft)
		{
			if (CollisionChecker({ position.x - waterActionRange, position.y }, { position.x,position.y + size }, obj))
			{
				enemy->SetDead();
			}
		}
		else
		{
			if (CollisionChecker({ position.x + size,position.y }, { position.x + size + waterActionRange,position.y + size }, obj))
			{
				enemy->SetDead();
			}
		}
		enemy = nullptr;
	}
}

void Prince::ItemCollision(double, Object::Base*& item)
{
	switch (item->GetType())
	{
	case Object::Type::Helium:
	{
		Object::Helium* HeliumItem = (Object::Helium*)item;
		if (!HeliumItem->wasTaken())
		{
			HeliumItem->Taken();
			SetHelium();
			EM.Add(new GetHeliumeffect({{GetPosition()+(GetSize()/2)},{GetPosition() + (GetSize() / 2)}}));
		}
		HeliumItem = nullptr;
	}
	break;

	case Object::Type::Candy:
	{
		Object::Candy* CandyItem = (Object::Candy*)item;
		if (!CandyItem->wasTaken())
		{
			CandyItem->Taken();
			SetCandy();
			EM.Add(new GetCandyEffect({ {GetPosition() + GetSize() / 2},{GetPosition() + GetSize() / 2} }));
		}
		CandyItem = nullptr;
	}
	break;
	case Object::Type::UP_1:

		Object::UP1* Up_1Item = (Object::UP1*)item;
		if (!Up_1Item->wasTaken())
		{
			Up_1Item->Taken();
			startPos = Up_1Item->GetPos();
			saveit = true;
			EM.Add(new GetSaveEffect({{GetPosition() + GetSize()/2},{GetPosition()+GetSize()/2}}));
		}
		Up_1Item = nullptr;
		break;
	}

}

void Prince::AreaCollision(double dt, Object::Area*& area)
{
	switch (area->GetType())
	{

	case Object::Type::Wind:

		if (GetBalloonState() != BALLOONSTATE::Water)
		{
			Object::Wind* WA{ (Object::Wind*)area };
			intoWind = true;

			switch (WA->GetDirection())
			{
			case Effect::DIRECTION::Left:
				velocity.x -= Object::Wind::windPower;
				if (velocity.x < currBalloon->GetMinVel().x)
				{
					velocity.x = currBalloon->GetMinVel().x;
				}
				break;
			case Effect::DIRECTION::Right:
				velocity.x += Object::Wind::windPower;
				if (velocity.x > currBalloon->GetMaxVel().x)
				{
					velocity.x = currBalloon->GetMaxVel().x;
				}
				break;
			case Effect::DIRECTION::Up:
				velocity.y += currBalloon->GetGravity() * 2 * dt;
				if (velocity.y > currBalloon->GetMaxVel().y)
				{
					velocity.y = currBalloon->GetMaxVel().y;
				}
				break;
			case Effect::DIRECTION::Down:
				velocity.y -= currBalloon->GetGravity() * 2 * dt;
				if (velocity.y < currBalloon->GetMinVel().y)
				{
					velocity.y = currBalloon->GetMinVel().y;
				}
				break;
			}

			WA = nullptr;
		}
		break;

	case Object::Type::Water:
		if (this->currBalloon->GetState() == BALLOONSTATE::Electric)
		{
			ChangeBalloon(BALLOONSTATE::Normal);
		}
		intoWater = true;
		break;
	}
}

void Prince::OnPlatformUpdate(double dt, Object::Base*& block)
{
	position.y = block->GetPos().y + block->GetSize();
	position.x += block->GetVelocity().x * dt;
	velocity.y = 0;
	if (block->GetType() == Object::Type::Moving)
	{
		onMoveBlock = true;
	}
	if (currBalloon->GetState() != BALLOONSTATE::Helium)
	{
		InteractFurry(block);
		InteractOnOff(block);
		bool isMoveBlock = block->GetType() == Object::Type::Moving || block->GetType() == Object::Type::OnOff;
		if (isMoveBlock == true)
		{
			Object::Moving* obj = (Object::Moving*)block;
			velocity.y = -obj->accel * 2;
			obj = nullptr;
		}

	}
	onPlatform = true;
}

void Prince::InteractFurry(Object::Base*& block)
{
	if (block->GetType() == Object::Type::Furry)
	{
		if (position.y < block->GetPos().y + block->GetSize())
		{
			SideFurryBlock = true;
		}
		else
		{
			onFurryBlock = true;
		}
	}
}

void Prince::InteractPlant(Object::Plant*& p)
{
	if (std::pow(p->GetPos().x - position.x, 2.0) + std::pow(p->GetPos().y - position.y, 2.0) 
		<= std::pow(Object::Block::size * 3, 2.0)) // if it prince is in 3 block distance 
	{
		if (currState == &stateSprinkle) {

			if (p->GetPos().x < position.x) { // plant is left side
				if (watchLeft == true)
					p->SetGrow(true);
			}
			else {
				if (watchLeft == false)
					p->SetGrow(true);
			}
			p = nullptr;
		}

	}
}

void Prince::BlockCollision(double dt, Object::Base*& block)
{
	const math::vec2 p = position;
	const math::vec2 b = block->GetPos();
	const double pSize = size;
	const double bSize = block->GetSize();
	double xextent;
	double yextent;
	bool left = false;
	bool top = false;
	if (p.x < b.x) {
		left = true;
		xextent = (pSize + bSize) - (b.x + bSize - p.x);
	}
	else {
		xextent = (pSize + bSize) - (p.x + pSize - b.x);
	}
	if (p.y < b.y) {
		yextent = (pSize + bSize) - (b.y + bSize - p.y);
	}
	else {
		top = true;
		yextent = (pSize + bSize) - (p.y + pSize - b.y);
	}
	if (xextent < yextent) {
		if (left) {
			InteractFurry(block);
			position.x = b.x - pSize;
		}
		else {
			InteractFurry(block);
			position.x = b.x + bSize;
		}
	}
	else if (xextent > yextent) {
		if (xextent >= 5) {
			if (top) {
				OnPlatformUpdate(dt, block);
				position.y = b.y + bSize;
			}
			else {
				velocity.y = 0;
				position.y = b.y - pSize;
			}
		}
	}
	if (block->GetType() == Object::Type::Spike && isInvisible == false && isDead == false)
	{
		SetIsHitted();
		MonsterShove(block);
	}
}

void Prince::InteractOnOff(Object::Base*& block)
{
	if (block->GetType() == Object::Type::OnOff && currBalloon->GetState() == BALLOONSTATE::Electric)
	{
		Object::OnOff* onOffBlock = (Object::OnOff*)block;
		onOffBlock->SetOnOff(true);
	}
}

void Prince::MonsterShove(Object::Base*& enemy)
{
	const math::vec2 p = position;
	const math::vec2 b = enemy->GetPos();
	const double pSize = size;
	const double bSize = enemy->GetSize();
	if (p.x < b.x)
	{
		velocity.x = -shovePower;
		velocity.y = shovePower;
	}
	else
	{
		velocity.x = shovePower;
		velocity.y = shovePower;
	}

}

void Prince::MonsterCollision(double, Object::Base*& obj)
{
	Object::Enemy_base* enemy = (Object::Enemy_base*)obj;

	if (enemy->IsDead() == false)
	{
		enemy->SetCollide();
		if (isDash == true && enemy->GetType() != Object::Type::Robot)
		{
			Engine::getEffectSound().PlaySounds(11);
			enemy->SetDead();
			isHitEnemy = true;
			
		}
		else if (isInvisible == false)
		{
			SetIsHitted();
			MonsterShove(obj);
		}
	}

	enemy = nullptr;
}

void Prince::spriteUpdate(double dt)
{
	switch (GetBalloonState())
	{
	case BALLOONSTATE::Normal:
	case BALLOONSTATE::Helium:
		sprite.Update(dt);
		break;
	case BALLOONSTATE::Flat:
		sprite_Flat.Update(dt);
		break;
	case BALLOONSTATE::Electric:
		sprite_Electric.Update(dt);
		sprite_Effect.Update(dt);
		break;
	case BALLOONSTATE::Water:
		sprite_Water.Update(dt);
		break;
	default:
		break;
	}
}

void Prince::SetIsInvisible(double time)
{
	InvisibleTime = time;
	InvisibleTimer = 0;
	isInvisible = true;
}

double Prince::GetSize() const
{
	return size; // static constexpr size;
}

math::vec2 Prince::GetPosition() const
{
	return position;
}
math::vec2 Prince::GetStartPos() const
{
	return startPos;
}

int Prince::GetHelium() const
{
	return helium;
}
//int Prince::GetLife() const
//{
//	return Life;
//}
bool Prince::GetGameover() const
{
	return false; // Life < 0;
}

bool Prince::GetIsDash() const
{
	return isDash;
}

void Prince::SetIsHitted()
{
	if (isHitted == false && currState != &stateDead)
	{
		SetIsInvisible(AfterHittedInvisibleTime);
		ChangeState(&stateGetDamage);
	}
}

void Prince::SetHelium()
{
	helium++;
	if (helium == 2)
	{
		ChangeState(&stateFlying);
		ChangeBalloon(BALLOONSTATE::Helium);
	}
}

void Prince::SetCandy()
{
	candy = true;
}

bool Prince::GetIsDead() const
{
	return isDead;
}

int Prince::GetWaterActionCount() const
{
	return WaterActionCount;
}


Prince::BALLOONSTATE Prince::GetBalloonState() const
{
	return currBalloon->GetState();
};

void Prince::Cheat()
{

	if (changeNormal.IsKeyReleased() == true)
	{
		ChangeBalloon(BALLOONSTATE::Normal);
		Engine::getLogger().LogDebug("Normal state");
	}
	else if (changeFlat.IsKeyReleased() == true)
	{
		ChangeBalloon(BALLOONSTATE::Flat);
		Engine::getLogger().LogDebug("Flat state");

	}
	else if (changeElectric.IsKeyReleased() == true)
	{
		ChangeBalloon(BALLOONSTATE::Electric);
		Engine::getLogger().LogDebug("Electric state");

	}
	else if (changeWater.IsKeyReleased() == true)
	{
		ChangeBalloon(BALLOONSTATE::Water);
		Engine::getLogger().LogDebug("Water state");

	}
	else if (getHelium.IsKeyReleased() == true)
	{
		helium += 1;
		if (helium == 2)
		{
			ChangeState(&stateFlying);
			ChangeBalloon(BALLOONSTATE::Helium);
		}
		if (helium >= 2)
		{
			helium = 2;
		}
	}
	else if (loseHelium.IsKeyReleased() == true)
	{
		helium -= 1;
		if (helium < 0)
		{
			helium = 0;
		}
	}
	else if (InvisibleKey.IsKeyReleased() == true)
	{
		SetIsInvisible(AfterDashInvisibleTime);
	}
	else if (GODKEY.IsKeyPressed() == true)
	{
		if (currState == &stateGOD)
		{
			SetStateGOD(false);
		}
		else
		{
			SetStateGOD(true);
		}
	}
}

void Prince::SetStateGOD(bool b)
{
	GODMODE = b;
	if (b)
	{
		ChangeState(&stateGOD);
	}
	else
	{
		SetIsInvisible(1);
		ChangeState(&stateIdle);
	}
}

bool Prince::CanInteract() const
{
	if(GetBalloonState() == BALLOONSTATE::Normal)
	{
		return onFurryBlock || SideFurryBlock || intoWater;
	}
	return false;
}
