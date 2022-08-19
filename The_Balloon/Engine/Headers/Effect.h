/*
File Name: Effect.h
Project Name: The balloon
Author(s)
Main:Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#pragma once
#include <vector>
#include <doodle/angle.hpp>

#include "Particle.h"

class Prince;

class Effect
{
	friend class EffectManager;
public:
	enum class DIRECTION
	{
		Left,
		Right,
		Up,
		Down

	};
protected:
	std::vector<Particle*> particles;
	
	math::rect2 startArea;
	double minAngle{ 0 };
	double maxAngle{ 0 };

	double minSize{ 0 };
	double maxSize{ 0 };
	double minSpeed{ 0 };
	double maxSpeed{ 0 };
	double minParticleTime{ 0 };
	double maxParticleTime{ 0 };
	double effectTime{ 1 };
	double effectTimer{ 0 };
	bool loop = false;
	double loopTimer = 0;
	double MaxParticle{ 100 };

	double cycle{1};
	double amount{1};

	Effect() = default;
	virtual ~Effect() { Clear(); }
	virtual void Update(double dt) = 0;
	virtual void Draw(const DOG::Camera& cam);
	virtual void Draw(const DOG::Camera& cam, double scale);
	virtual void Draw() {};
	template<typename T>
	void Add();

	
	void SetSize(double s) { minSize = s, maxSize = s; }
	void SetAngle(double a) { minAngle = a, maxAngle = a; }
	void SetSpeed(double s) { minSpeed = s, maxSpeed = s; }
	void SetParticleTime(double pt) { minParticleTime = pt, maxParticleTime = pt; }
	void SetSize(double mins, double maxs) { minSize = mins, maxSize = maxs; }
	void SetAngle(double mina, double maxa) { minAngle = mina, maxAngle = maxa; }
	void SetSpeed(double mins, double maxs) { minSpeed = mins, maxSpeed = maxs; }
	void SetParticleTime(double minpt, double maxpt) { minParticleTime = minpt, maxParticleTime = maxpt; }
	void Clear()
	{
		for (auto particle : particles)
		{
			delete particle;
		}
		particles.clear();
	}
	virtual bool IsEnd() { return effectTime <= effectTimer; } //ÀÌÆåÆ®°¡ ²¨Áö´Â Á¶°Ç
};

class WindEffect : public Effect
{
	math::rect2 windArea;
public:

	WindEffect(math::rect2 windArea, math::rect2 startArea, DIRECTION direction);
	~WindEffect() {}
	
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	void Draw(const DOG::Camera& cam, double scale) override;
	void Draw() override;
	void FindAngle(DIRECTION direction);
	bool IsEnd() override;
};

class SprinkleEffect : public Effect
{
public:
	SprinkleEffect(math::rect2 startArea, DIRECTION direction);
	~SprinkleEffect() {}
	
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	void Draw(const DOG::Camera& cam, double scale) override;
	void FindAngle(DIRECTION direction);
};

class DashEffect : public Effect
{

public:
	const Prince* prince;
	DashEffect(math::rect2 startArea, DIRECTION direction, Prince& p);
	~DashEffect() {}

	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	void Draw(const DOG::Camera& cam, double scale) override;

	void FindAngle(DIRECTION direction);
	bool IsEnd() override;
};

class IntoWaterEffect : public Effect
{

public:
	IntoWaterEffect(math::rect2 startArea);
	~IntoWaterEffect() {}

	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	void Draw(const DOG::Camera& cam, double scale) override;
	bool IsEnd() override;
};

class jumpEffect : public Effect
{
public:
	jumpEffect(math::rect2 startArea);
	~jumpEffect() {}

	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	bool IsEnd() override;
	void Draw(const DOG::Camera& cam, double scale) override;
};

class normalJumpEffect : public jumpEffect
{
public:
	normalJumpEffect(math::rect2 startArea);
	~normalJumpEffect(){}
};

class waterJumpEffect : public jumpEffect
{
public:
	waterJumpEffect(math::rect2 startArea);
	~waterJumpEffect(){}
};

class flatJumpEffect : public jumpEffect
{
public:
	flatJumpEffect(math::rect2 startArea);
	~flatJumpEffect(){}
};

class electricJumpEffect : public jumpEffect
{
public:
	electricJumpEffect(math::rect2 startArea);
	~electricJumpEffect(){}
};


class GetItemEffect : public Effect
{
public:
	GetItemEffect(math::rect2 startArea);
	~GetItemEffect() {}

	void Update(double dt) override;
	bool IsEnd() override;
};

class GetHeliumeffect : public Effect
{
public:
	GetHeliumeffect(math::rect2 startArea);
	~GetHeliumeffect() {}

	void Update(double dt) override;
	bool IsEnd() override;
};

class GetCandyEffect : public Effect
{
public:
	GetCandyEffect(math::rect2 startArea);
	~GetCandyEffect() {}

	void Update(double dt) override;
	bool IsEnd() override;
};

class GetSaveEffect : public Effect
{
public:
	GetSaveEffect(math::rect2 startArea);
	~GetSaveEffect() {}

	void Update(double dt) override;
	bool IsEnd() override;
};