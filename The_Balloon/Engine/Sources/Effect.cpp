/* my work
File Name: Effect.cpp
Project Name: The balloon
Author(s)
Main:Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include "../Headers/Effect.h"
#include "../../Game/Headers/Prince.h"
#include <doodle/random.hpp>

template <typename T> //T must be particle
void Effect::Add()
{
	for (int i = 0; i < amount; i++)
	{
	math::vec2 position;
	if (startArea.bottomLeft.x == startArea.topRight.x) { position.x = startArea.bottomLeft.x; }
	else { position.x = doodle::random(startArea.bottomLeft.x, startArea.topRight.x); }
	if (startArea.bottomLeft.y == startArea.topRight.y) { position.y = startArea.bottomLeft.y; }
	else { position.y = doodle::random(startArea.bottomLeft.y, startArea.topRight.y); }
		
	double angle;
	if (minAngle == maxAngle) { angle = minAngle; }
	else { angle = doodle::random(minAngle, maxAngle); }
		
	double speed;
	if (minSpeed == maxSpeed) { speed = minSpeed; }
	else { speed = doodle::random(minSpeed, maxSpeed); }
		
	double size;
	if (minSize == maxSize) { size = minSize; }
	else { size = doodle::random(minSize, maxSize); }

	double particleTime;
	if (minParticleTime == maxParticleTime) { particleTime = minParticleTime; }
	else { particleTime = doodle::random(minParticleTime, maxParticleTime); }
		
	particles.push_back(new T(position, angle, particleTime, speed, size));
	}
}

void Effect::Draw(const DOG::Camera& cam)
{
	for (auto p : particles)
	{
		p->Draw(cam);
	}
}

void Effect::Draw(const DOG::Camera& cam, double scale)
{
	for (auto p : particles)
	{
		p->Draw(cam,scale);
	}
}



WindEffect::WindEffect(math::rect2 windArea, math::rect2 startArea, DIRECTION direction)
	: Effect()
{
	this ->windArea = windArea;
	this->startArea = startArea;
	MaxParticle = 100;
	amount = 1;
	loop = true;
	cycle = 0.1;
	SetParticleTime(10);
	SetSpeed(800, 1100);
	effectTime = 1000;
	SetSize(8);
	FindAngle(direction);
	Add<WindParticle>();
}


void WindEffect::Update(double dt)
{

	for (int i = 0; i < particles.size(); ++i)
	{
		particles[i]->Update(dt);
		math::vec2 pPosition = particles[i]->GetPosition();
		if (pPosition.x < windArea.Left() || pPosition.x > windArea.Right() || pPosition.y < windArea.Bottom() || pPosition.y > windArea.Top())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
		else if (particles[i]->IsDead())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}

	}
	if (loop && loopTimer >= cycle)
	{
		loopTimer = 0;
		Add<WindParticle>();
	}
	if (particles.size() > MaxParticle)
	{
		delete particles[0];
		particles.erase(particles.begin());
	}
	loopTimer += dt;
	effectTimer += dt;
}

void WindEffect::Draw(const DOG::Camera& cam)
{
	for (auto p : particles)
	{
		p->Draw(cam);
	}
}

void WindEffect::Draw(const DOG::Camera& cam, double scale)
{
	for (auto p : particles)
	{
		p->Draw(cam, scale);
	}
}

void WindEffect::Draw()
{
	for (auto p : particles)
	{
		p->Draw();
	}
}


void WindEffect::FindAngle(DIRECTION direction)
{
	switch (direction)
	{
	case DIRECTION::Right:
		SetAngle(0);
		break;
	case DIRECTION::Down:
		SetAngle(doodle::PI*1.5);
		break;
	case DIRECTION::Left:
		SetAngle(doodle::PI);
		break;
	case DIRECTION::Up:
		SetAngle(doodle::PI*0.5);
		break;
		
	}
}

bool WindEffect::IsEnd()
{
	//ÀÌÆåÆ®°¡ ²¨Áö´Â Á¶°Ç
	
	return false;
}


void SprinkleEffect::Update(double dt)
{
	effectTimer += dt;
	for (int i = 0; i < particles.size(); ++i)
	{
		particles[i]->Update(dt);
		if (particles[i]->IsDead())
		{
			particles.erase(particles.begin() + i);
		}
	}
	if (particles.size() > MaxParticle)
	{
		delete particles[0];
		particles.erase(particles.begin());
	}
}


SprinkleEffect::SprinkleEffect(math::rect2 startArea, DIRECTION direction) : Effect()
{
	this->startArea = startArea;
	
	MaxParticle = 60;
	amount = 60;
	loop = false;
	SetSpeed(400, 600);
	effectTime = 1;
	SetSize(32);
	FindAngle(direction);
	SetParticleTime(1);
	Add<WaterParticle>();
}


void SprinkleEffect::Draw(const DOG::Camera& cam)
{
	for (auto p : particles)
	{
		p->Draw(cam);
	}
}

void SprinkleEffect::Draw(const DOG::Camera& cam, double scale)
{
	for (auto p : particles)
	{
		p->Draw(cam, scale);
	}
}

void SprinkleEffect::FindAngle(DIRECTION direction)
{
	switch (direction)
	{
	case DIRECTION::Right:
		SetAngle(0, doodle::PI * 0.3);
		break;

	case DIRECTION::Left:
		SetAngle(doodle::PI * 0.7, doodle::PI);
		break;
;

	}
}

DashEffect::DashEffect(math::rect2 startArea, DIRECTION direction, Prince& p)
	:prince(&p)
{
	this->startArea = startArea;
	MaxParticle = 100;
	amount = 2;
	loop = true;
	cycle = 0.08;
	effectTime = 0.5;
	SetParticleTime(0.5);
	SetSpeed(400, 600);
	SetSize(8,16);
	FindAngle(direction);
	Add<DashParticle>();
}

void DashEffect::Update(double dt)
{
	if (prince->watchLeft == true)
	{
		startArea = 
		{ math::vec2(prince->GetPosition().x + prince->GetSize(),prince->GetPosition().y + prince->GetSize() / 4),
		   math::vec2(prince->GetPosition().x + prince->GetSize(),prince->GetPosition().y + prince->GetSize() / 4) };
	}
	else
	{
		startArea = { math::vec2(prince->GetPosition().x,prince->GetPosition().y + prince->GetSize() / 4),
						math::vec2(prince->GetPosition().x,prince->GetPosition().y + prince->GetSize() / 4) };
	}
	for(int i = 0; i < particles.size();++i)
	{
		particles[i]->Update(dt);
		if(particles[i]->IsDead())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
	if (loop && loopTimer >= cycle)
	{
		loopTimer = 0;
		Add<DashParticle>();
	}
	if (particles.size() > MaxParticle)
	{
		delete particles[0];
		particles.erase(particles.begin());
	}
	if(effectTime <= effectTimer)
	{
		loop = false;
	}
	loopTimer += dt;
	effectTimer += dt;
}

void DashEffect::FindAngle(DIRECTION direction)
{
	switch (direction)
	{
	case DIRECTION::Right:
		SetAngle(doodle::PI * 1.8,doodle::PI * 2.20);
		break;

	case DIRECTION::Left:
		SetAngle(doodle::PI * 0.8, doodle::PI* 1.20);
		break;
	}
}

void DashEffect::Draw(const DOG::Camera& cam)
{
	for (auto p : particles)
	{
		p->Draw(cam);
	}
}

void DashEffect::Draw(const DOG::Camera& cam, double scale)
{
	for (auto p : particles)
	{
		p->Draw(cam, scale);
	}
}

bool DashEffect::IsEnd()
{
	if(particles.empty())
	{
		return true;
	}
	return false;
}

IntoWaterEffect::IntoWaterEffect(math::rect2 startArea)
{
	this->startArea = startArea;
	MaxParticle = 100;
	amount = 10;
	loop = false;
	cycle = 0;
	effectTime = 0.8;
	SetParticleTime(0.2, effectTime);
	SetSpeed(400, 600);
	SetSize(32);
	SetAngle(0, doodle::PI);
	Add<WaterParticle>();
}

void IntoWaterEffect::Update(double dt)
{
	effectTimer += dt;
	for (int i = 0; i < particles.size(); ++i)
	{
		particles[i]->Update(dt);
		if (particles[i]->IsDead())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
	if (particles.size() > MaxParticle)
	{
		delete particles[0];
		particles.erase(particles.begin());
	}
}

void IntoWaterEffect::Draw(const DOG::Camera& cam)
{
	for (auto p : particles)
	{
		p->Draw(cam);
	}
}

void IntoWaterEffect::Draw(const DOG::Camera& cam, double scale)
{
	for (auto p : particles)
	{
		p->Draw(cam, scale);
	}
}

bool IntoWaterEffect::IsEnd()
{
	return effectTime <= effectTimer;
}


jumpEffect::jumpEffect(math::rect2 startArea)
{
	this->startArea = startArea;
	MaxParticle = 10;
	amount = 10;
	loop = false;
	cycle = 0;
	effectTime = 0.8;
	SetParticleTime(0.2, effectTime);
	SetSpeed(400, 600);
	SetSize(16);
	SetAngle(0, doodle::PI);
}


void jumpEffect::Update(double dt)
{
	for (int i = 0; i < particles.size(); ++i)
	{
		particles[i]->Update(dt);
		if (particles[i]->IsDead())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
	if (particles.size() > MaxParticle)
	{
		delete particles[0];
		particles.erase(particles.begin());
	}
	if (effectTime <= effectTimer)
	{
		loop = false;
	}
	effectTimer += dt;
}

void jumpEffect::Draw(const DOG::Camera& cam)
{
	for (auto p : particles)
	{
		p->Draw(cam);
	}
}

void jumpEffect::Draw(const DOG::Camera& cam, double scale)
{
	for (auto p : particles)
	{
		p->Draw(cam, scale);
	}
}


bool jumpEffect::IsEnd()
{
	return effectTime <= effectTimer;
}

normalJumpEffect::normalJumpEffect(math::rect2 startArea)
	: jumpEffect(startArea)
{
	Add<JumpParticle>();
}

waterJumpEffect::waterJumpEffect(math::rect2 startArea) : jumpEffect(startArea)
{
	SetSpeed(200, 400);
	Add<WaterParticle>();
}

flatJumpEffect::flatJumpEffect(math::rect2 startArea) : jumpEffect(startArea)
{

	MaxParticle = 5;
	amount = 5;
	SetSpeed(100, 200);
	SetSize(4);
	Add<JumpParticle>();
}
electricJumpEffect::electricJumpEffect(math::rect2 startArea) : jumpEffect(startArea)
{
	SetSpeed(100, 300);
	SetSize(4);
	Add<electricParticle>();
}


GetItemEffect::GetItemEffect(math::rect2 startArea)
{
	this->startArea = startArea;
	MaxParticle = 10;
	amount = 6;
	loop = false;
	cycle = 0;
	effectTime = 0.8;
	SetParticleTime(0.5, effectTime);
	SetSpeed(20, 40);
	SetSize(16);
	SetAngle(doodle::PI * 0.5);
	Add<HeartParticle>();
}

void GetItemEffect::Update(double dt)
{
	effectTimer += dt;
	for (int i = 0; i < particles.size(); ++i)
	{
		particles[i]->Update(dt);
		if (particles[i]->IsDead())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
}

bool GetItemEffect::IsEnd()
{
	return effectTime <= effectTimer;	
}

GetHeliumeffect::GetHeliumeffect(math::rect2 startArea)
{
	this->startArea = startArea;
	MaxParticle = 30;
	amount = 1;
	loop = false;
	cycle = 0;
	effectTime = 0.8;
	SetParticleTime(effectTime);
	SetSpeed(270,300);
	SetSize(16);
/*	SetAngle(0, doodle::TWO_PI);
	Add<StarParticle>()*/;
	for (int i = 1; i < 9; ++i)
	{
		SetAngle(doodle::TWO_PI / 8 * i);
		Add<StarParticle>();
	}
}
GetCandyEffect::GetCandyEffect(math::rect2 startArea)
{
	this->startArea = startArea;
	MaxParticle = 30;
	amount = 1;
	loop = false;
	cycle = 0;
	effectTime = 0.8;
	SetParticleTime(effectTime);
	SetSpeed(270, 300);
	SetSize(8);

		for (int i = 1; i < 9; ++i)
		{
			SetAngle(doodle::TWO_PI / 8 * i);
			Add<Star2Particle>();
		}
}

void GetCandyEffect::Update(double dt)
{
	effectTimer += dt;
	for (int i = 0; i < particles.size(); ++i)
	{
		particles[i]->Update(dt);
		if (particles[i]->IsDead())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
}

bool GetCandyEffect::IsEnd()
{
	return effectTime <= effectTimer;
}



void GetHeliumeffect::Update(double dt)
{
	effectTimer += dt;
	for (int i = 0; i < particles.size(); ++i)
	{
		particles[i]->Update(dt);
		if (particles[i]->IsDead())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
}

bool GetHeliumeffect::IsEnd()
{
	return effectTime <= effectTimer;
}


GetSaveEffect::GetSaveEffect(math::rect2 startArea)
{
	this->startArea = startArea;
	MaxParticle = 1;
	amount = 1;
	loop = false;
	cycle = 0;
	effectTime = 1;
	SetParticleTime(effectTime);
	SetAngle(doodle::PI * 0.5);
	SetSpeed(200);
	Add<SaveParticle>();
}

void GetSaveEffect::Update(double dt)
{
	effectTimer += dt;
	for (int i = 0; i < particles.size(); ++i)
	{
		particles[i]->Update(dt);
		if (particles[i]->IsDead())
		{
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}
}

bool GetSaveEffect::IsEnd()
{
	return effectTime <= effectTimer;
}
