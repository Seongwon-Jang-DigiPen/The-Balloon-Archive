/*
File Name: Window.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include <doodle/window.hpp>
#include <doodle/drawing.hpp>
#include "../Headers/Engine.h"
#include "../Headers/Window.h"

void DOG::Window::Init(std::string winName)
{
	doodle::create_window(winName, 1280, 720);
	doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginBottomLeft);
}

void DOG::Window::Update() { doodle::update_window(); }

void DOG::Window::Clear(unsigned int color) { doodle::clear_background(doodle::HexColor(color)); }

math::ivec2 DOG::Window::GetSize() { return windowSize; }

void DOG::Window::Resize(int new_width, int new_height) 
{
	windowSize.x = new_width;
	windowSize.y = new_height;
}

// doodle
void on_window_resized(int new_width, int new_height) 
{
	Engine::getLogger().LogEvent("Window Resized");
	Engine::getWindow().Resize(new_width, new_height);
}