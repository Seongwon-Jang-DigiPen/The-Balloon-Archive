/*
File Name: Sound.h
Project Name: The balloon
Author(s)
Main: Sangbeom Kim
Sub: Seongwon Jang
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include <SFML/Audio.hpp>


namespace DOG
{
class Sound {
protected:
	std::vector<sf::SoundBuffer> SoundBuffers{};
	std::vector<sf::Sound>       Sounds{};
	sf::Sound::Status status = sf::SoundSource::Playing;
	int volume = 20;

public:
   void LoadSound(const std::string& file_path);
   virtual void PlaySounds(int i);
   virtual void Setup();
	void SetPause();
	void SetPlaying();
	void SetSound(int volume);
	void Unload();
	sf::Sound::Status GetStatus() { return status; }
};


class BGM : public Sound
{
public:
	void PlaySounds(int i) override;
	void Setup() override;
};
}