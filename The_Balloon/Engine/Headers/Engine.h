/*
File Name: Engine.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once

#include <chrono>
#include "GSManager.h"
#include "Input.h"
#include "Window.h"
#include "Logger.h"
#include "SaveManager.h"
#include "TextureManager.h"
#include "Sound.h"
#include "../../Game/Headers/GameMap.h"
class Engine
{
public:
	static Engine& Reference() { static Engine ref; return ref; }

	void Init(std::string winName);
	void Shutdown();
	void Update();
	bool HasGameEnded();

	void SetdeveloperMode() { developerMode = true; }
	bool CheckdeveloperMode() { return developerMode; }
	static DOG::GSManager& getGSManager() { return Reference().GSmanager; };
	static DOG::Logger& getLogger() { return Reference().logger; }
	static DOG::Window& getWindow() { return Reference().window; }
	static DOG::InputSystem& getInput() { return Reference().input; }
	static DOG::TextureManager& getTextureManager() { return Reference().textureManager; }
	static DOG::Sound& getEffectSound() { return Reference().EffectSound; }
	static DOG::BGM& getBackgroundSound() { return Reference().BackgroundSound; }
	static SaveManager& getSaveManager() { return Reference().saveManager; }
	
private:
	Engine();
	~Engine();

	DOG::GSManager GSmanager;
	DOG::Logger logger;
	DOG::Window window;
	DOG::InputSystem input;
	DOG::TextureManager textureManager;
	DOG::Sound EffectSound;
	DOG::BGM BackgroundSound;
	SaveManager saveManager;

	std::chrono::system_clock::time_point lastTick;
	std::chrono::system_clock::time_point currentTick;
	int frameCount;

	bool wasLoaded = false;

	bool developerMode = false;
	
	static constexpr double Target_FPS = 60.0;
	static constexpr int FPS_IntervalSec = 5;
	static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec * Target_FPS);
};

