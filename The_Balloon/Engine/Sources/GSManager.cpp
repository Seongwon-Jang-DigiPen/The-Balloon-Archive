/*
File Name: GSManager.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include "../Headers/GSManager.h"
#include "../Headers/Engine.h"
#include "../Headers/GameState.h"

DOG::GSManager::GSManager() 
{
	currGameState = nextGameState = nullptr;
	state = State::START;
}

void DOG::GSManager::AddState(GameState& gamestate) { gameStates.push_back(&gamestate); }

void DOG::GSManager::Update(double dt) 
{
	switch (state)
	{
	case DOG::GSManager::State::START:
		if (gameStates.size() == 0) {
			Engine::getLogger().LogError("Failed to Load");
			state = State::SHUTDOWN;
			break;
		}

		nextGameState = gameStates[0];
		state = State::LOAD;
		break;
	case DOG::GSManager::State::LOAD:
		currGameState = nextGameState;
		Engine::getLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		state = State::UPDATE;
		break;
	case DOG::GSManager::State::UPDATE:
		if (nextGameState != currGameState) 
		{
			state = State::UNLOAD;
		}
		else
		{
			Engine::getLogger().LogVerbose("Update");
			currGameState->Update(dt);
			currGameState->Draw();
		}
		break;
	case DOG::GSManager::State::UNLOAD:
		Engine::getLogger().LogEvent("Unload " + currGameState->GetName());
		currGameState->Unload();
		(nextGameState == nullptr) ? state = State::SHUTDOWN : state = State::LOAD;
		break;
	case DOG::GSManager::State::SHUTDOWN:
		state = State::EXIT;
		break;
	case DOG::GSManager::State::EXIT:
		break;
	default:
		break;
	}
}

void DOG::GSManager::SetNextState(int initState) { nextGameState = gameStates[initState]; }

void DOG::GSManager::Shutdown() { nextGameState = nullptr; }

void DOG::GSManager::Reload() { state = State::UNLOAD; }

bool DOG::GSManager::HasGameEnded() { return state == State::EXIT; }

