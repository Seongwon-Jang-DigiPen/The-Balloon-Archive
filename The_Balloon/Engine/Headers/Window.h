/*
File Name: Window.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#pragma once
#include <string>
#include "Vec2.h"

namespace DOG 
{
	class Window
	{
	public:
		void Init(std::string winName);
		void Update();
		void Clear(unsigned int color);
		
		void Resize(int width, int height);
		math::ivec2 GetSize();
	private:
		math::ivec2 windowSize;
	};
}