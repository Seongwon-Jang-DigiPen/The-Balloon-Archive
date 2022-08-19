/*
File Name: Sound.cpp
Project Name: The balloon
Author(s)
Main: Sangbeom Kim
Sub: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include "../Headers/Sound.h"

[[noreturn]] void error(const std::string& s) { throw std::runtime_error(s); }

void DOG::Sound::Setup() {
    LoadSound("Assets/sound/Balloon_FlatToNormal_Sound.wav");//0
    LoadSound("Assets/sound/Balloon_Jump_Sound.wav");
    LoadSound("Assets/sound/Balloon_NormalToWater_Sound.wav");
    LoadSound("Assets/sound/Balloon_Dash_Sound.wav");
    LoadSound("Assets/sound/Balloon_NormalToElectric_Sound.wav");
    LoadSound("Assets/sound/Balloon_Dashhit_sound.wav"); //5
    LoadSound("Assets/sound/Item_Get_Helium.wav");
    LoadSound("Assets/sound/Mapeditor_Button.wav");
    LoadSound("Assets/sound/Mapeditor_Block.wav");
    LoadSound("Assets/sound/Splash_Effect.wav");//9
    LoadSound("Assets/sound/Cut_Scene0.wav");
    LoadSound("Assets/sound/Balloon_HitMonster_Sound.wav");
}

void DOG::Sound::LoadSound(const std::string& file_path)
{
    SoundBuffers.emplace_back();
    sf::SoundBuffer& buffer = SoundBuffers.back();
	
    if (!buffer.loadFromFile(file_path))
    {
        error("Failed to load " + file_path);
    }
}

void DOG::Sound::PlaySounds(int i)
{
    int buffer_index = i;
    for (auto& sound : Sounds)
    {
        if (sound.getStatus() != sf::SoundSource::Playing)
        {
            sound.setBuffer(SoundBuffers[buffer_index]);
            sound.play();
        	return;
        }
    }
    Sounds.emplace_back(SoundBuffers[buffer_index]);
    Sounds.back().setVolume(volume);
    Sounds.back().play();
}

void DOG::Sound::SetPause()
{
    status = sf::SoundSource::Paused;
    for (auto& sound : Sounds)
    {
        sound.pause();
    }
}

void DOG::Sound::SetPlaying()
{
    status = sf::SoundSource::Playing;
    for (auto& sound : Sounds)
    {
        sound.play();
    }
}

void DOG::Sound::SetSound(int v)
{
    volume = v;
    for (auto& sound : Sounds)
    {
        sound.setVolume(volume);
    }
}

void DOG::Sound::Unload()
{
    status = sf::SoundSource::Stopped;
    for (auto& sound : Sounds)
    {
        sound.stop();
    }
}


void DOG::BGM::Setup()
{
    LoadSound("Assets/sound/Chapter1_BG_Sound.wav"); 
    LoadSound("Assets/sound/MainMenu_BG_Sound.wav");
    LoadSound("Assets/sound/Credit_BG_Sound.wav");
    LoadSound("Assets/sound/Chapter2_BG_Sound.wav");
}


void DOG::BGM::PlaySounds(int i)
{
    int buffer_index = i;
    for (auto& sound : Sounds)
    {
        if (sound.getStatus() != sf::SoundSource::Playing)
        {
            sound.setBuffer(SoundBuffers[buffer_index]);
            sound.play();
            return;
        }
    }
    Sounds.emplace_back(SoundBuffers[buffer_index]);
    Sounds.back().setLoop(true);
    Sounds.back().setVolume(volume);
    SetSound(30);
    switch (GetStatus())
    {
    case sf::SoundSource::Playing:
        Sounds.back().play();
        break;
    case sf::SoundSource::Paused:
        Sounds.back().pause();
        break;
    case sf::SoundSource::Stopped:
        Sounds.back().stop();
        break;
    }
}
