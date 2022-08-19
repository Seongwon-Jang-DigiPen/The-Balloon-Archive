/*
File Name: Sprite.cpp
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include <fstream>
#include "../Headers/Sprite.h"
#include "../Headers/Engine.h"
#include "../Headers/Animation.h" 
DOG::Sprite::Sprite() : currAnim(0), texturePtr(nullptr) {}

void DOG::Sprite::Load(const std::filesystem::path& spriteInfoFile) {
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() != ".spt") {
		throw std::runtime_error("Bad Filetype.  " + spriteInfoFile.generic_string() + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
	}

	std::string text;
	inFile >> text;
	texturePtr = Engine::getTextureManager().Load(text);
	frameSize = texturePtr->GetSize();

	inFile >> text;
	while (inFile.eof() == false) {
		if (text == "FrameSize") {
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		else if (text == "NumFrames") {
			int numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++) {
				frameTexel.push_back({ frameSize.x * i, 0 });
			}
		}
		else if (text == "Frame") {
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		}
		else if (text == "HotSpot") {
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpotList.push_back({ hotSpotX, hotSpotY });
		}
		else if (text == "Anim") {
			std::filesystem::path path;
			inFile >> path;
			animations.push_back(new Animation{ path });
		}
		else {
			Engine::getLogger().LogError("Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
	if (animations.empty() == true) {
		animations.push_back(new Animation{});
	}
}

void DOG::Sprite::PlayAnimation(int anim)
{
	if (animations.size() <= anim && anim > 0)
	{
		Engine::getLogger().LogError("Index value not exist in animations");
		currAnim = 0;
	}
	else { currAnim = anim; }
	animations[currAnim]->ResetAnimation();
};

void DOG::Sprite::Update(double dt)
{
	if (IsAnimationDone() == false)
	{
		animations[currAnim]->Update(dt);
	}
};

bool DOG::Sprite::IsAnimationDone()
{
	if (animations[currAnim]->IsAnimationDone() == true) { return true; }
	else { return false; }
};

int DOG::Sprite::GetAnimationIndex() {
	return animations[currAnim]->GetAnimationIndex();
}

math::ivec2 DOG::Sprite::GetFrameSize() const
{
	return frameSize;
};

math::ivec2 DOG::Sprite::GetFrameTexel(int frameNum) const
{
	if (frameTexel.size() <= frameNum)
	{
		Engine::getLogger().LogError("Invalid FrameTexel frameNum");
		return { 0,0 };
	}
	return frameTexel[frameNum];
}

void DOG::Sprite::Draw(math::vec2 location, bool flip)
{
	texturePtr->Draw(location, GetFrameTexel(animations[currAnim]->GetDisplayFrame()), frameSize , flip);
};

void DOG::Sprite::Draw(math::vec2 location , int index)
{
	texturePtr->Draw(location, GetFrameTexel(index), frameSize);
};

math::ivec2 DOG::Sprite::GetHotSpot(int index)
{
	if (hotSpotList.size() <= index)
	{
		Engine::getLogger().LogError("Invalid hotspot index");
		return { 0,0 };
	}
	else { return hotSpotList[index]; }
};

DOG::Sprite::~Sprite() {
	for (Animation* anim : animations) {
		delete anim;
	}
	animations.clear();
}