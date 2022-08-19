/*
File Name: PrinceState.cpp
Project Name: The balloon
Author(s)
Main: Seongwon Jang
Sub: Sehun Kim, Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../../Engine/Headers/Engine.h" // logger
#include "../Headers/Prince.h"
#include "../../Engine/Headers/Effect.h"

//Animation
void Prince::Animation(Prince_Anim ani)
{
	switch (GetBalloonState())
	{
	case BALLOONSTATE::Normal:
		sprite.PlayAnimation(static_cast<int>(ani));
		break;
	case BALLOONSTATE::Flat :
		sprite_Flat.PlayAnimation(static_cast<int>(ani));
		break;
	case BALLOONSTATE::Electric:
		sprite_Electric.PlayAnimation(static_cast<int>(ani));
		break;
	case BALLOONSTATE::Water:
		sprite_Water.PlayAnimation(static_cast<int>(ani));
		break;
	default:
		break;
	}
}

//Jump
void Prince::State_Jumping::Enter(Prince* prince)
{
	if(prince->helium == 1)
	{
		prince->jumpPower = prince->currBalloon->GetHeliumJumpVel();
	}
	else
	{
		prince->jumpPower = prince->currBalloon->GetJumpVel();
	}
	
	math::vec2 bottomCenter{ prince->position.x + prince->size / 2, prince->position.y };


	switch (prince->GetBalloonState())
	{
	case BALLOONSTATE::Normal:
		prince->EM.Add(new normalJumpEffect({ bottomCenter,bottomCenter }));
		break;
	case BALLOONSTATE::Flat:
		prince->EM.Add(new flatJumpEffect({ bottomCenter,bottomCenter }));
		break;
	case BALLOONSTATE::Water:
		prince->EM.Add(new waterJumpEffect({ bottomCenter,bottomCenter }));
		break;
	case BALLOONSTATE::Electric:
		prince->EM.Add(new electricJumpEffect({ bottomCenter,bottomCenter }));
		break;
	}
	
	finished_pressed = false;
	prince->velocity.y = prince->jumpPower / 2;
	prince->jumpTime = 0;
	prince->jumpPower /= 2;
	Engine::getEffectSound().PlaySounds(1);

	if (prince->GetBalloonState() != BALLOONSTATE::Flat)
	prince->Animation(Prince_Anim::Prince_Jump_Anim);
}
void Prince::State_Jumping::Update(Prince* prince, double dt)
{
	prince->jumpTime += dt;
	if (prince->jumpKey.IsKeyDown() == true) {
		if (prince->jumpTime > jumpUpdateCycle && !finished_pressed)
		{
		prince->jumpPower /= 2;
		prince->velocity.y += prince->jumpPower;
		prince->jumpTime = 0;
		}
	}
	else if(prince->jumpKey.IsKeyDown() == false)
	{
		finished_pressed = true;
	}
	prince->velocity.y -= prince->currBalloon->GetGravity() * dt;
	prince->velocity.y -= prince->currBalloon->GetAirResistance().y * dt;


	
}
void Prince::State_Jumping::TestForExit(Prince* prince)
{
	if (prince->velocity.y <= 0) {
		prince->ChangeState(&prince->stateFalling);
	}
}

//Idle
void Prince::State_Idle::Enter(Prince* prince)
{
	prince->Animation(Prince_Anim::Prince_Idle_Anim);
}
void Prince::State_Idle::Update(Prince*, double)
{

}
void Prince::State_Idle::TestForExit(Prince* prince)
{
	if (prince->jumpKey.IsKeyDown() == true)
	{
		prince->ChangeState(&prince->stateJumping);
	}
	else if (prince->moveLeftKey.IsKeyDown() == true || prince->moveRightKey.IsKeyDown() == true)
	{
		prince->ChangeState(&prince->stateRunning);
	}
	else if (prince->onPlatform == false)
	{
		prince->ChangeState(&prince->stateFalling);
	}
	else if (prince->interactKey.IsKeyPressed() == true && (prince->onFurryBlock == true || prince->SideFurryBlock == true) && prince->currBalloon->GetState() == BALLOONSTATE::Normal)
	{
		prince->ChangeState(&prince->stateRubbing);
	}
	else if(prince->intoWater == true && prince->GetBalloonState() != BALLOONSTATE::Water)
	{
		prince->ChangeState(&prince->stateSwimming);
	}
}
//Running
void Prince::State_Running::Enter(Prince* prince) 
{
	prince->Animation(Prince_Anim::Prince_Run_Anim);
}
void Prince::State_Running::Update(Prince*, double)
{
	
}
void Prince::State_Running::TestForExit(Prince* prince)
{
	if (prince->jumpKey.IsKeyDown() == true)
	{
		prince->ChangeState(&prince->stateJumping);
	}
	else if (prince->velocity.x == 0)
	{
		prince->ChangeState(&prince->stateIdle);
	}
	else if(prince->onPlatform == false)
	{
		prince->ChangeState(&prince->stateFalling);
	}
	else if (prince->interactKey.IsKeyPressed() == true && (prince->onFurryBlock == true || prince->SideFurryBlock == true) && prince->currBalloon->GetState() == BALLOONSTATE::Normal)
	{
		prince->ChangeState(&prince->stateRubbing);
	}
	if (prince->intoWater == true && prince->GetBalloonState() != BALLOONSTATE::Water)
	{
		prince->ChangeState(&prince->stateSwimming);
	}
}
//Falling
void Prince::State_Falling::Enter(Prince* prince) 
{
	prince->Animation(Prince_Anim::Prince_Fall_Anim);
}
void Prince::State_Falling::Update(Prince* prince, double dt)
{

	prince->velocity.y -= prince->currBalloon->GetGravity() * dt;
	if (prince->velocity.y < prince->currBalloon->GetMinVel().y)
	{
		prince->velocity.y = prince->currBalloon->GetMinVel().y;
	}
}
void Prince::State_Falling::TestForExit(Prince* prince)
{
	if (prince->onPlatform == true)
	{
		if (prince->velocity.x == 0)
		{
			prince->ChangeState(&prince->stateIdle);
		}
		else
		{
			prince->ChangeState(&prince->stateRunning);
		}
	}
	if(prince->moveDownKey.IsKeyDown() == true && prince->intoWind == false)
	{
		prince->ChangeState(&prince->stateFallingFast);
	}
	if (prince->intoWater == true && prince->GetBalloonState() != BALLOONSTATE::Water)
	{
		prince->ChangeState(&prince->stateSwimming);
	}
}
//FallingFast
void Prince::State_FallingFast::Enter(Prince* prince)
{
	prince->velocity.y = prince->descentSpeed;
}
void Prince::State_FallingFast::Update(Prince* prince, double)
{
	prince->velocity.y = prince->descentSpeed;
}
void Prince::State_FallingFast::TestForExit(Prince* prince)
{
	if (prince->onPlatform == true)
	{
		if (prince->velocity.x == 0)
		{
			prince->ChangeState(&prince->stateIdle);
		}
		else
		{
			prince->ChangeState(&prince->stateRunning);
		}
	}
	if (prince->moveDownKey.IsKeyDown() == false || prince->intoWind == true)
	{
		prince->ChangeState(&prince->stateFalling);
	}
	if (prince->intoWater == true && prince->GetBalloonState() != BALLOONSTATE::Water)
	{
		prince->ChangeState(&prince->stateSwimming);
	}
}

//Flying
void Prince::State_Flying::Enter(Prince* prince)
{
	prince->sprite.PlayAnimation(static_cast<int>(Prince_Anim::Prince_Fly_Anim));
}
void Prince::State_Flying::Update(Prince* prince, double dt)
{
	prince->velocity.y += prince->currBalloon->GetGravity() * dt;
	if (prince->velocity.y > prince->currBalloon->GetMaxVel().y)
	{
		prince->velocity.y = prince->currBalloon->GetMaxVel().y;
	}
	
	if(prince->moveDownKey.IsKeyPressed() == true)
	{
		prince->velocity.y = -prince->currBalloon->GetJumpVel();
	}
}
void Prince::State_Flying::TestForExit(Prince* prince)
{
	//when player arrive the Hub -> Idle
	if(prince->helium < 2)
	{
		prince->ChangeState(&prince->stateIdle);
	}
}

//Dash
[[maybe_unused]] void Prince::State_Dash::Enter(Prince* prince)
{
	Engine::getLogger().LogEvent("Dash!");
	prince->candy = false;
	prince->isDash = true;
	if(prince->watchLeft)
	{
		prince->EM.Add(new DashEffect(
			{ math::vec2(prince->position.x + prince->size,prince->position.y + prince->size/4),
				math::vec2(prince->position.x + prince->size,prince->position.y + prince->size / 4) },
						Effect::DIRECTION::Right, *prince));
	}
	else 
	{
		prince->EM.Add(new DashEffect(
			{ math::vec2(prince->position.x,prince->position.y + prince->size / 4),
						math::vec2(prince->position.x,prince->position.y + prince->size / 4) }, 
					Effect::DIRECTION::Left, *prince));
	}
	Engine::getEffectSound().PlaySounds(3);
	prince->Animation(Prince_Anim::Prince_Dash_Anim);

	if (prince->watchLeft == true)
	{
		prince->velocity = -DashSpeed;
	}
	else
	{
		prince->velocity = DashSpeed;
	}
}
void Prince::State_Dash::Update(Prince* prince, double dt)
{
	if (prince->watchLeft == true)
	{
		prince->velocity.x += DashSpeed.x * dt;
	}
	else
	{
		prince->velocity.x -= DashSpeed.x * dt;
	}
	Timer += dt;
}
void Prince::State_Dash::TestForExit(Prince* prince)
{
	if(prince->sprite.IsAnimationDone())
	{
		prince->velocity.x = 0;
		Timer = 0;
		prince->isDash = false;
		prince->doAction = false;
		prince->SetIsInvisible(AfterDashInvisibleTime);
		if (prince->candy)
		{
			prince->candy = false;
			prince->ChangeBalloon(Prince::BALLOONSTATE::Normal);
			prince->ChangeState(&prince->stateFalling);
		}
		else
		{
			prince->ChangeBalloon(BALLOONSTATE::Flat);
			prince->ChangeState(&prince->stateFalling);
		}
	}
}

//GetAir
void Prince::State_GetAir::Enter(Prince* prince)
{

	Engine::getEffectSound().PlaySounds(0);
	prince->hardcoding = 0;
	if(prince->GetBalloonState() == BALLOONSTATE::Helium)
		prince->sprite_Flat.PlayAnimation(6);
	else
		prince->sprite_Flat.PlayAnimation(5);
}
void Prince::State_GetAir::Update(Prince* prince, double dt)
{
	prince->velocity.x = 0;
	prince->size += (48 - 20) / actionTime * dt;
	prince->position.x -= ((48 - 20) / actionTime * dt) / 2;
	prince->hardcoding += hardcodingvalue / actionTime * dt;
	Timer += dt;
}
void Prince::State_GetAir::TestForExit(Prince* prince)
{
	if (prince->sprite_Flat.IsAnimationDone())
	{
		prince->hardcoding = 0;
		Timer = 0;
		prince->doAction = false;
		if (prince->helium > 1)
		{
			prince->ChangeBalloon(BALLOONSTATE::Helium);
			prince->ChangeState(&prince->stateFlying);
		}
		else
		{
			prince->ChangeBalloon(BALLOONSTATE::Normal);
			prince->ChangeState(&prince->stateIdle);
		}
	}
}

//Rubbing
void Prince::State_Rubbing::Enter(Prince* prince)
{
	Timer = 0;
	prince->doAction = true;
	if(prince->SideFurryBlock == true)
		prince->sprite.PlayAnimation(static_cast<int>(Prince_Anim::Prince_Rubbing2_Anim));
	else prince->sprite.PlayAnimation(static_cast<int>(Prince_Anim::Prince_Rubbing_Anim));
}
void Prince::State_Rubbing::Update(Prince* prince, double dt)
{
	prince->velocity = 0;
	Timer += dt;
}
void Prince::State_Rubbing::TestForExit(Prince* prince)
{
	if(Timer >= actionTime)
	{
		prince->doAction = false;
		prince->ChangeBalloon(BALLOONSTATE::Electric);
		prince->ChangeState(&prince->stateIdle);
	}
}

//Dead
void Prince::State_Dead::Enter(Prince* prince)
{
	prince->SetIsInvisible(actionTime);
	prince->sprite_Flat.PlayAnimation(4);
}
void Prince::State_Dead::Update(Prince* prince, double dt)
{
	Timer += dt;
	prince->velocity = 0;
}
void Prince::State_Dead::TestForExit(Prince* prince)
{
	if (Timer >= actionTime)
	{
		prince->isDead = true;
	}
}
//Sprinkle
void Prince::State_Sprinkle::Enter(Prince* prince)
{
	if (prince->GetWaterActionCount() == 1)
		prince->sprite_Water.PlayAnimation(5);
	else prince->sprite_Water.PlayAnimation(6);

	prince->velocity = 0;
	prince->waterActionRange = 0;
	if(prince->sprinkleAll)
	{
		prince->WaterActionCount = 0;
	}
	else
	{
		--prince->WaterActionCount;
	}
	if (prince->watchLeft)
	{
		prince->EM.Add(new SprinkleEffect({
			{prince->position.x, prince->position.y },
			{prince->position.x+1, prince->position.y + prince->size} }
		, Effect::DIRECTION::Left));
	}
	else
	{
		prince->EM.Add(new SprinkleEffect({
			{prince->position.x + prince->size, prince->position.y },  
			{prince->position.x + prince->size+1, prince->position.y + prince->size} }
		, Effect::DIRECTION::Right));
	}

}
void Prince::State_Sprinkle::Update(Prince* prince, double dt)
{
	Timer += dt;
	prince->waterActionRange += waterActionRangeMax / actionTime * dt;
}
void Prince::State_Sprinkle::TestForExit(Prince* prince)
{
	if (Timer >= actionTime)
	{
		prince->sprinkleAll = false;
		if (prince->WaterActionCount <= 0)
		{
			prince->WaterActionCount = 3;
			prince->ChangeBalloon(BALLOONSTATE::Normal);
		}
		Timer = 0;
		prince->doAction = false;
		prince->ChangeState(&prince->stateIdle);
	}
	
}

//GetWater
void Prince::State_GetWater::Enter(Prince* prince)
{
	prince->sprite.PlayAnimation(static_cast<int>(Prince_Anim::Prince_GetWater_Anim));
}
void Prince::State_GetWater::Update(Prince* prince, double dt)
{
	prince->velocity = 0;
	Timer += dt;
}
void Prince::State_GetWater::TestForExit(Prince* prince)
{
	if (Timer >= actionTime)
	{
		Timer = 0;
		prince->doAction = false;
		prince->ChangeBalloon(BALLOONSTATE::Water);
		prince->ChangeState(&prince->stateIdle);
	}
}

//GetDamaged
void Prince::State_GetDamage::Enter(Prince* prince)
{
	prince->isHitted = true;
	prince->doAction = true;
	prince->Animation(Prince_Anim::Prince_Damaged_Anim);
	prince->sprite.PlayAnimation(static_cast<int>(Prince_Anim::Prince_Damaged_Anim));
	Engine::getEffectSound().PlaySounds(5);
}
void Prince::State_GetDamage::Update(Prince* prince, double dt)
{
	Timer += dt;
	
	if (0 > prince->velocity.x) {
		if (prince->velocity.x > -prince->shovePower * dt) {
			Engine::getLogger().LogVerbose("Stopped");
			prince->velocity.x = 0;
		}
		else {
			Engine::getLogger().LogVerbose("+Dragging");
			prince->velocity.x += prince->shovePower * dt;
		}
	}
	if (0 < prince->velocity.x)
	{
		if (prince->velocity.x < prince->shovePower * dt) {
			Engine::getLogger().LogVerbose("Stopped");
			prince->velocity.x = 0;
		}
		else {
			Engine::getLogger().LogVerbose("-Dragging");
			prince->velocity.x -= prince->shovePower * dt;
		}
	}

	prince->velocity.y -= prince->currBalloon->GetGravity() * dt;
}
void Prince::State_GetDamage::TestForExit(Prince* prince)
{
	if (Timer > actionTime) {

		prince->isHitted = false;
		prince->doAction = false;
		if (prince->GetBalloonState() == BALLOONSTATE::Flat)
		{
			Timer = 0;
			prince->ChangeState(&prince->stateDead);
		}
		else
		{
			Timer = 0;
			prince->ChangeBalloon(BALLOONSTATE::Flat);
			prince->ChangeState(&prince->stateIdle);
		}
	}
}

void Prince::State_Swimming::Enter(Prince* prince)
{
	prince->Animation(Prince_Anim::Prince_Fall_Anim);
	prince->EM.Add(new IntoWaterEffect(
		{{prince->position.x + prince->size / 2,prince->position.y}, 
					{prince->position.x + prince->size / 2,prince->position.y} }));
}

void Prince::State_Swimming::Update(Prince* prince, double dt)
{
	
	prince->velocity.y += prince->currBalloon->GetGravity() * dt;
	if (prince->velocity.y > prince->currBalloon->GetMaxVel().y)
	{
		prince->velocity.y = prince->currBalloon->GetMaxVel().y;
	}
	
}

void Prince::State_Swimming::TestForExit(Prince* prince)
{
	if(prince->interactKey.IsKeyPressed() == true && prince->currBalloon->GetState() == BALLOONSTATE::Normal)
	{
		prince->ChangeState(&prince->stateGetWater);
	}
	if(prince->intoWater == false)
	{
		if (prince->onPlatform == true)
		{
			if (prince->velocity.x == 0)
			{
				prince->ChangeState(&prince->stateIdle);
			}
			else
			{
				prince->ChangeState(&prince->stateRunning);
			}
		}
		else
		{
			prince->ChangeState(&prince->stateFalling);
		}
	}
	if (prince->GetBalloonState() == BALLOONSTATE::Water)
	{
		prince->ChangeState(&prince->stateIdle);
	}
}



/////////////////////////
//B_Helium
void Prince::Balloon_Helium::Enter(Prince* prince)
{
	prince->size = this->size;
	Engine::getEffectSound().PlaySounds(6);
}
void Prince::Balloon_Helium::TestForExit(Prince* prince)
{
	if(prince->helium < 2)
	{
		prince->doAction = false;
		prince->ChangeBalloon(BALLOONSTATE::Normal);
	}
}
//B_Normal
void Prince::Balloon_Normal::Enter(Prince* prince)
{
	prince->size = this->size;
}
void Prince::Balloon_Normal::TestForExit(Prince*)
{
}
//B_Flat
void Prince::Balloon_Flat::Enter(Prince* prince)
{
	prince->size = this->size;
}
void Prince::Balloon_Flat::TestForExit(Prince* prince)
{
	if(prince->candy)
	{
		prince->candy = false;
		prince->ChangeBalloon(Prince::BALLOONSTATE::Normal);
	}
}
//B_Electric
void Prince::Balloon_Electric::Enter(Prince* prince)
{
	prince->size = this->size;
	Engine::getEffectSound().PlaySounds(4);
}
[[maybe_unused]] void Prince::Balloon_Electric::TestForExit(Prince*) {}
//B_Water
void Prince::Balloon_Water::Enter(Prince* prince)
{
	prince->WaterActionCount = 3;
	prince->size = this->size;
	Engine::getEffectSound().PlaySounds(2);
}
[[maybe_unused]] void Prince::Balloon_Water::TestForExit(Prince*) {}
///////////////////////////////////////////


void Prince::ChangeState(State* newState)
{
	Engine::getLogger().LogDebug("Leaving State: " + currState->GetName() + " Entering State: " + newState->GetName());
	currState = newState;
	currState->Enter(this);
}
void Prince::ChangeBalloon(BALLOONSTATE state)
{
	Engine::getLogger().LogDebug("Leaving Balloon: " + currBalloon->GetName());
	delete currBalloon;
	currBalloon = nullptr;
	switch (state)
	{
	case BALLOONSTATE::Normal:
		currBalloon = new Balloon_Normal;
		break;
	case BALLOONSTATE::Flat:
		currBalloon = new Balloon_Flat;
		break;
	case BALLOONSTATE::Electric:
		currBalloon = new Balloon_Electric;
		break;
	case BALLOONSTATE::Water:
		currBalloon = new Balloon_Water;
		break;
	case BALLOONSTATE::Helium:
		currBalloon = new Balloon_Helium;
		break;
	}

	Engine::getLogger().LogDebug("Entering Balloon: " + currBalloon->GetName());
	currBalloon->Enter(this);
}


void Prince::State_GOD::Enter(Prince* prince)
{
	prince->velocity = 0;
	prince->SetIsInvisible(10000);
}
void Prince::State_GOD::Update(Prince* prince, double dt)
{
	prince->SetIsInvisible(10000);
	if (prince->moveLeftKey.IsKeyDown() == true)
	{
		prince->position.x -= prince->xAcceleration / 3 * dt;
	}
	if (prince->moveRightKey.IsKeyDown() == true)
	{
		prince->position.x += prince->xAcceleration / 3 * dt;
	}
	if (prince->moveDownKey.IsKeyDown() == true)
	{
		prince->position.y -= prince->xAcceleration / 3 * dt;
	}
	if (prince->moveUpKey.IsKeyDown() == true)
	{
		prince->position.y += prince->xAcceleration / 3 * dt;
	}
		prince->velocity = 0;
	
}
void Prince::State_GOD::TestForExit(Prince* prince)
{
	if (prince->GODMODE == false)
	{
		prince->SetIsInvisible(1);
		prince->ChangeState(&prince->stateIdle);
	}
}

