/*
File Name: Chapter2.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang, Sehun Kim, Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#pragma once
#include "../../Engine/Headers/Engine.h"
#include "../../Engine/Headers/GameState.h"
#include "../../Engine/Headers/Camera.h"
#include "../../Engine/Headers/Input.h"

#include "MapEditor.h"
#include "Prince.h"
#include "Pause.h"
#include "GameOver.h"
#include "UI.h"

class Chapter2 : public DOG::GameState {
    using TileChunk = GameMap::MapChunk;

public:
    Chapter2();

    static constexpr double floor = 126.0f;
    static constexpr double clearY = 6 * 16 * 64;

    void Load() override;
    void Draw() override;
    void Update(double dt) override;
    void Unload() override;

    std::string GetName() override { return "Level 2"; }
private:

    DOG::Sprite Background;
    DOG::Sprite Star;
    DOG::Texture map2;
    //doodle::Image Backgorund{"assets/Back/background.png"};

    UI ui;
    Pause pause;
    //End end;
    Anim enter_a;
    Anim Ending_a;
    Prince prince;
    //DOG::Texture background;

    DOG::Camera camera;
    DOG::Input levelReload, shakeKey, cheat_clear;
    //DOG::Input levelReload;


    GameMap map;
    MapEditor editor;

    double start_x = Engine::getWindow().GetSize().x / 2;
    double start_y = Engine::getWindow().GetSize().y / 2;

    bool has_started;
    bool has_ended;
    int time;
};