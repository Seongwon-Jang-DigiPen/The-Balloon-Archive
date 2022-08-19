/*
File Name: Engine.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include "../Headers/Engine.h"

Engine::Engine()
	:	frameCount(0),
		lastTick(std::chrono::system_clock::now()),
		logger(DOG::Logger::Severity::Debug, lastTick)
{}

Engine::~Engine() {}

void Engine::Init(std::string winName) 
{
	getBackgroundSound().Setup();
	getEffectSound().Setup();
	currentTick = lastTick;
	logger.LogEvent("Engine Init");
	window.Init(winName);
}

void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
	//GameMaps.erase(GameMaps.begin());
	//GameMaps[0].Unload();
	//GameMaps[1].Unload();
	//GameMaps.clear();
}

void Engine::Update()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();

	if (dt >= 1 / Engine::Target_FPS) {
		logger.LogVerbose("Engine Update");
		GSmanager.Update(dt);
		input.Update();
		window.Update();

		frameCount++;
		if (frameCount >= Engine::FPS_IntervalFrameCount) {
			double updateTime = std::chrono::duration<double>(now - currentTick).count();
			double averageFrameRate = Engine::FPS_IntervalFrameCount / updateTime;
			logger.LogEvent("FPS:  " + std::to_string(averageFrameRate));
			frameCount = 0;
			currentTick = now;
		}
		lastTick = now;
	}

}


bool Engine::HasGameEnded() { return GSmanager.HasGameEnded(); }