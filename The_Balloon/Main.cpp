/*
File Name: Main.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim, Seongwon Jang, Sehun Kim, Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <stdexcept>	//std::exception
#include <iostream>		//std::cerr
#include <crtdbg.h>

#include "Engine/Headers/Engine.h"

#include "Game/Headers/Splash.h"
#include "Game/Headers/Main_Screen.h"
#include "Game/Headers/CutScene.h"
#include "Game/Headers/Setting.h"
#include "Game/Headers/Tutorial.h"
#include "Game/Headers/Chapter2.h"
#include "Game/Headers/Credit.h"
#include "Game/Headers/GameOver.h"

int main(void) {
	try {
#if _DEBUG
		HWND hWndConsole = GetConsoleWindow();
		ShowWindow(hWndConsole, SW_SHOW);
#else
		HWND hWndConsole = GetConsoleWindow();
		ShowWindow(hWndConsole, SW_HIDE);
#endif
		Engine& engine = Engine::Reference();
		engine.Init("The Balloon");
		Splash splash;
		Main main;
		CutScene cutscene0(0);
		CutScene cutscene1(1);
		CutScene cutscene2(2);
		CutScene cutscene3(3);
		CutScene cutscene4(4);
		CutScene loadscene(5);
		CutScene cutscene5(6);
		CutScene cutscene6(7);
		CutScene loadscene2(8);
		CutScene cutscene7(9);
		Tutorial tutorial;
		Chapter2 chapter2;
		Setting setting;
		GameOver gameover;
		Credit credit;

		engine.getGSManager().AddState(splash);
		engine.getGSManager().AddState(main);
		engine.getGSManager().AddState(cutscene0);
		engine.getGSManager().AddState(cutscene1);
		engine.getGSManager().AddState(cutscene2);
		engine.getGSManager().AddState(cutscene3);
		engine.getGSManager().AddState(cutscene4);
		engine.getGSManager().AddState(loadscene);
		engine.getGSManager().AddState(cutscene5);
		engine.getGSManager().AddState(cutscene6);
		engine.getGSManager().AddState(loadscene2);
		engine.getGSManager().AddState(cutscene7);
		engine.getGSManager().AddState(tutorial);
		engine.getGSManager().AddState(chapter2);
		engine.getGSManager().AddState(setting);
		engine.getGSManager().AddState(credit);
		engine.getGSManager().AddState(gameover);
		cutscene0.ImageLoad();
		cutscene1.ImageLoad();
		cutscene2.ImageLoad();
		cutscene3.ImageLoad();
		cutscene4.ImageLoad();
		loadscene.ImageLoad();
		cutscene5.ImageLoad();
		cutscene6.ImageLoad();
		loadscene2.ImageLoad();
		cutscene7.ImageLoad();
		Engine::getEffectSound().Setup();
		Engine::getBackgroundSound().Setup();

		while (engine.HasGameEnded() == false) {
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << "\n";
		return -1;
	}
}