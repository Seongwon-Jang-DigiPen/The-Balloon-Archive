/*
File Name: GSManager.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include <vector>

namespace DOG
{
	class GameState; // pre-declaration (NOT kind of include something)

	class GSManager
	{
	public:
		GSManager();

		void AddState(GameState& gState);
		void Update(double dt);
		void SetNextState(int initState);
		void Shutdown();
		void Reload();
		bool HasGameEnded();
	private:
		enum class State { START, LOAD, UPDATE, UNLOAD, SHUTDOWN, EXIT };
		
		std::vector<GameState*> gameStates;
		State state;
		GameState* currGameState;
		GameState* nextGameState;
	};
}
