/* my work
File Name: Particle.h
Project Name: The balloon
Author(s)
Main: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include <doodle/color.hpp>
#include <doodle/image.hpp>


#include "Vec2.h"

namespace DOG {
	class Camera;
}

struct Particle
{
	math::vec2 position{ 0 };
	math::vec2 velocity{ 0 };
	doodle::Color color{255,255,255,255};
	double size{ 10 };
	double speed{ 0 };
	double angle{ 0 };
	double Size{10};
	double time{ 1 };
	double timer{ 0 };
	bool isDead = false;
	static constexpr double gravity = 128;

	Particle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	virtual ~Particle() {}

	virtual void Update(double dt);
	virtual void Draw(const DOG::Camera& cam);
	virtual void Draw(const DOG::Camera& cam, double scale);
	virtual void Draw();
	void SetPosition(math::vec2 pos);
	void SetVelocity(math::vec2 vel);
	void SetSpeed(double speed);
	void SetAngle(double angle);
	math::vec2 GetPosition() { return position; }
	math::vec2 GetVelocity() { return velocity; }
	double GetSpeed() { return speed; }
	double GetAngle() { return angle; }
	bool IsDead() { return isDead; }
};

struct WindParticle : public Particle
{
	WindParticle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~WindParticle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;

};

struct WaterParticle : public Particle
{

	const double initsize = 0;
	double drag{ 0.95 };
	WaterParticle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~WaterParticle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;

};

struct DashParticle : public Particle
{
	const double initsize = 0;
	double drag{ 0.95 };
	DashParticle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~DashParticle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;

};

struct JumpParticle : public Particle
{
	const double initsize = 0;
	double drag{ 0.95 };
	JumpParticle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~JumpParticle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;

};

struct electricParticle : public Particle
{
	doodle::Color yellow{ 255,255,0,205 };
	
	bool changecolor = false;
	electricParticle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~electricParticle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;
};

struct HeartParticle : public Particle
{
	HeartParticle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~HeartParticle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;
	
	doodle::Image particleImage{ "Assets/Effect/heart.png" };
	
};

struct StarParticle : public Particle
{
	double drag{ 0.97 };
	StarParticle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~StarParticle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;

	doodle::Image particleImage{ "Assets/Effect/star1.png" };
};

struct Star2Particle : public Particle
{
	double drag{ 0.97 };
	Star2Particle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~Star2Particle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;
	doodle::Image particleImage{ "Assets/Effect/star2.png" };
};

struct SaveParticle : public Particle
{
	double drag{ 0.97 };
	SaveParticle(math::vec2 Position, double Angle, double Time, double Speed, double size);
	~SaveParticle() {}
	void Update(double dt) override;
	void Draw(const DOG::Camera& cam) override;
	virtual void Draw(const DOG::Camera& cam, double scale) override;

	doodle::Image particleImage{ "Assets/Effect/Save.png" };
};