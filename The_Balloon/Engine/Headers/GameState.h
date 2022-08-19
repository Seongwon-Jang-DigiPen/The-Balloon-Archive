/*
File Name: GameState.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include <string>

namespace DOG
{
	class GameState 
	{
	public:
		virtual void Load() = 0;
		virtual void Draw() = 0;
		virtual void Update(double dt) = 0;
		virtual void Unload() = 0;
		virtual std::string GetName() = 0;
		enum class Chapter { DEFAULT, CHAPTER1, CHAPTER2, CHAPTERBOSS };
		Chapter chapter = Chapter::DEFAULT;
	};
}