/*
File Name: CutScene.h
Project Name: The balloon
Author(s)
Main: Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/GameState.h"
#include "../../Engine/Headers/Input.h"
#include "../../Engine/Headers/Sprite.h"
#include "GameOver.h"
#include <vector>

class CutScene : public DOG::GameState
{
public:

    CutScene(int statenow);
    void ImageLoad();
    void Load() override;
    void Update(double dt) override;
    void Draw() override;
    void Unload() override;

    std::string GetName() override { return "CutScene"; }
private:
    
    int stateNow;
    DOG::Sprite sprite;
    DOG::Input nextImage;
    DOG::Input skip;
    double time;
	
    class State {
    public:
        virtual void Enter(CutScene* cutscene) = 0;
        virtual void Update(CutScene* cutscene, double dt) = 0;
        virtual void TestForExit(CutScene* cutscene) = 0;
    };
    class State_Start : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    class State_Castle : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    class State_King : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    class State_King2 : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    class State_Exile : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    class State_Load : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };

    class State_1End : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    class State_2Start : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    class State_Load2 : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    class State_End : public State {
    public:
        virtual void Enter(CutScene* cutscene) override;
        virtual void Update(CutScene* cutscene, double dt) override;
        virtual void TestForExit(CutScene* cutscene) override;
    };
    State_Start statestart;
    State_Castle statecastle;
    State_King stateking;
    State_King2 stateking2;
    State_Exile stateexile;
    State_Load stateload;
    State_1End state1end;
    State_2Start state2start;
    State_Load2 stateload2;
    State_End stateend;

    void ChangeState(State* newState);
    State* currState;
    std::vector<State*> States{ &statestart, &statecastle, &stateking, &stateking2, &stateexile, &stateload, &state1end, &state2start, &stateload2, &stateend };
};