/*
File Name: Particle.cpp
Project Name: The balloon
Author(s)
Main: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include "../Headers/Particle.h"

#include "../../Game/Headers/Prince.h"
#include "../Headers/Camera.h"
#include "../Headers/Engine.h"
#include "doodle/doodle.hpp"

void Particle::SetPosition(math::vec2 pos)
{
	position = pos;
}

void Particle::SetVelocity(math::vec2 vel)
{
	velocity = vel;
}

void Particle::SetAngle(double a)
{
	this->angle = a;
}

void Particle::SetSpeed(double s)
{
	this->speed = s;
}

Particle::Particle(math::vec2 Position, double Angle, double Time, double Speed, double size)
: position(Position), angle(Angle), time(Time), speed(Speed), size(size)
{
	
}


void Particle::Update(double)
{
	/*timer += dt;
	velocity = { cos(angle) * speed,sin(doodle::PI * 2 * (timer + noiseOffset)) * (speed) };
	position += velocity * dt;*/
	//speed *= drag;
}

void Particle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::set_fill_color(255, 255, 255, 255);
	doodle::draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

void Particle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::set_fill_color(255,255,255,255);
	doodle::draw_rectangle(position.x , position.y, size, size);
	doodle::pop_settings();
}

void Particle::Draw()
{
	doodle::push_settings();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}


WindParticle::WindParticle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size)
{
	color = { 255,255,255,125 };
	velocity = { cos(angle) * speed,sin(angle) * speed };
}


void WindParticle::Update(double dt)
{
	timer += dt;
	position += velocity * dt;
	if(timer >= time)
	{
		isDead = true;
	}
}

void WindParticle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y, size, size);
	doodle::pop_settings();
}

void WindParticle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

WaterParticle::WaterParticle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size), initsize(size)
{
	color = { 55,55,255,125 };
	velocity = { cos(angle) * speed,sin(angle) * speed };
}

void WaterParticle::Update(double dt)
{
	timer += dt;
	position += velocity * dt;
	velocity *= drag;
	velocity.y -= gravity * dt;
	size -= initsize / time * dt;
	if (timer >= time)
	{
		isDead = true;
	}
	
}

void WaterParticle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y, size, size);
	doodle::pop_settings();
}

void WaterParticle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

DashParticle::DashParticle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size), initsize(size)
{
	color = { 255,255,255,150 };
	velocity = { cos(angle) * speed,sin(angle) * speed };
}


void DashParticle::Update(double dt)
{
	timer += dt;
	position += velocity * dt;
	velocity *= drag;
	size -= initsize / time * dt;
	if (timer >= time)
	{
		isDead = true;
	}
}


void DashParticle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y, size, size);
	doodle::pop_settings();
}

void DashParticle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

JumpParticle::JumpParticle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size), initsize(size)
{
	color = { 255,255,255,100 };
	velocity = { cos(angle) * speed,sin(angle) * speed };
}
void JumpParticle::Update(double dt)
{
	timer += dt;
	position += velocity * dt;
	velocity *= drag;
	size -= initsize / time * dt;
	if (timer >= time)
	{
		isDead = true;
	}
}

void JumpParticle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y, size, size);
	doodle::pop_settings();
}

void JumpParticle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(position.x, position.y, size, size);
	doodle::pop_settings();
}

electricParticle::electricParticle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size)
{
	color = yellow;
	velocity = { cos(angle) * speed,sin(angle) * speed };
}


void electricParticle::Update(double dt)
{
	timer += dt;
	position += velocity * dt;
	velocity.y -= gravity * 3.5 * dt;
	angle = atan2(velocity.y, velocity.x);

	if (timer >= time)
	{
		isDead = true;
	}
}


void electricParticle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::apply_rotate(angle);
	doodle::set_fill_color(color);
	doodle::draw_rectangle(0, 0, size, size/2);
	doodle::pop_settings();
}

void electricParticle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::apply_translate(position.x -cam.GetPosition().x, position.y -cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::apply_rotate(angle);
	doodle::no_outline();
	doodle::set_fill_color(color);
	doodle::draw_rectangle(0, 0, size, size/2);
	doodle::pop_settings();
}

HeartParticle::HeartParticle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size)
{
	velocity = { cos(angle) * speed,sin(angle) * speed };
}

void HeartParticle::Update(double dt)
{
	timer += dt;
	position += velocity * dt;

	if (timer >= time)
	{
		isDead = true;
	}
}

void HeartParticle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::draw_image(particleImage, 0, 0, size, size);
	doodle::pop_settings();
}

void HeartParticle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::no_outline();
	doodle::draw_image(particleImage,0,0, size, size);
	doodle::pop_settings();
}

StarParticle::StarParticle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size)
{
	velocity = { cos(angle) * speed,sin(angle) * speed };
}


void StarParticle::Update(double dt)
{

	timer += dt;
	position += velocity * dt;
	angle += 12*dt;
	velocity *= drag;
	if (timer >= time)
	{
		isDead = true;
	}

}

void StarParticle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_image_mode(doodle::RectMode::Center);
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::apply_rotate(angle);
	doodle::draw_image(particleImage, 0, 0, size, size);
	doodle::pop_settings();
}

void StarParticle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::set_image_mode(doodle::RectMode::Center);
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::apply_rotate(angle);
	doodle::no_outline();
	doodle::draw_image(particleImage, 0, 0, size, size);
	doodle::pop_settings();
}

Star2Particle::Star2Particle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size)
{
	velocity = { cos(angle) * speed,sin(angle) * speed };
}


void Star2Particle::Update(double dt)
{

	timer += dt;
	position += velocity * dt;
	angle += 12 * dt;
	velocity *= drag;
	if (timer >= time)
	{
		isDead = true;
	}

}

void Star2Particle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_image_mode(doodle::RectMode::Center);
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::apply_rotate(angle);
	doodle::draw_image(particleImage, 0, 0, size, size);
	doodle::pop_settings();
}

void Star2Particle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::set_image_mode(doodle::RectMode::Center);
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::apply_rotate(angle);
	doodle::no_outline();
	doodle::draw_image(particleImage, 0, 0, size, size);
	doodle::pop_settings();
}

SaveParticle::SaveParticle(math::vec2 Position, double Angle, double Time, double Speed, double size)
	: Particle(Position, Angle, Time, Speed, size)
{
	velocity = { cos(angle) * speed,sin(angle) * speed };
}


void SaveParticle::Update(double dt)
{
	timer += dt;
	position += velocity * dt;
	velocity *= drag;
	if (timer >= time)
	{
		isDead = true;
	}
}

void SaveParticle::Draw(const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::no_outline();
	doodle::set_image_mode(doodle::RectMode::Center);
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::draw_image(particleImage, 0, 0, 120, 51);
	doodle::pop_settings();
}

void SaveParticle::Draw(const DOG::Camera& cam, double scale)
{
	doodle::push_settings();
	doodle::set_image_mode(doodle::RectMode::Center);
	doodle::apply_translate(position.x - cam.GetPosition().x, position.y - cam.GetPosition().y);
	doodle::apply_scale(scale, scale);
	doodle::no_outline();
	doodle::draw_image(particleImage, 0, 0, 120, 51);
	doodle::pop_settings();
}
