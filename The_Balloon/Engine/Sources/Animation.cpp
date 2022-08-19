/*
File Name: Animation.cpp
Project Name: The balloon
Author(s)
Main:Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/Animation.h"
#include <fstream>

DOG::Animation::Animation() : Animation("./assets/none.anm") { }

DOG::Animation::Animation(const std::filesystem::path& fileName) : animSequenceIndex(0) {
	if (fileName.extension() != ".anm") {
		throw std::runtime_error("Bad Filetype.  " + fileName.generic_string() + " not a sprite info file (.anm)");
	}
	std::ifstream inFile(fileName);
	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + fileName.generic_string());
	}

	std::string label;
	while (inFile.eof() == false) {
		inFile >> label;
		if (label == "PlayFrame") {
			int frame;
			float targetTime;
			inFile >> frame;
			inFile >> targetTime;

			animation.push_back(new PlayFrame(frame, targetTime));
		}
		else if (label == "Loop") {
			int loopToFrame;
			inFile >> loopToFrame;
			animation.push_back(new Loop(loopToFrame));
		}
		else if (label == "End") {
			animation.push_back(new End());
		}
		else {
			Engine::getLogger().LogError("Unknown command " + label + " in anm file " + fileName.generic_string());
		}
	}
	ResetAnimation();
}

DOG::Animation::~Animation() {
	for (CommandData* command : animation) {
		delete command;
	}
	animation.clear();
}

void DOG::Animation::Update(double dt) {
	currPlayFrameData->Update(dt);
	if (currPlayFrameData->IsFrameDone() == true) {
		currPlayFrameData->ResetTime();
		++animSequenceIndex;
		if (animation[animSequenceIndex]->GetType() == Command::PlayFrame) {
			currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
		}
		else if (animation[animSequenceIndex]->GetType() == Command::Loop) {
			Loop* loopData = static_cast<Loop*>(animation[animSequenceIndex]);
			animSequenceIndex = loopData->GetLoopToIndex();
			if (animation[animSequenceIndex]->GetType() == Command::PlayFrame) {
				currPlayFrameData = static_cast<PlayFrame*>(animation[animSequenceIndex]);
			}
			else {
				Engine::getLogger().LogError("Loop does not go to PlayFrame");
				ResetAnimation();
			}
		}
		else if (animation[animSequenceIndex]->GetType() == Command::End) {
			isAnimationDone = true;
			return;
		}
	}
}

int DOG::Animation::GetDisplayFrame()
{
	return currPlayFrameData->GetFrameNum();
};

void DOG::Animation::ResetAnimation()
{
	animSequenceIndex = 0;
	isAnimationDone = false;
	currPlayFrameData = static_cast<PlayFrame*>(animation[0]);
};

bool DOG::Animation::IsAnimationDone()
{
	if (isAnimationDone == true) { return true; }
	else { return false; }
};

int DOG::Animation::GetAnimationIndex() {
	return animSequenceIndex;
}

DOG::Animation::PlayFrame::PlayFrame(int frame, double duration)
	: frame(frame), targetTime(duration), timer(0)
{}

void DOG::Animation::PlayFrame::Update(double dt)
{
	timer += dt;
};

bool DOG::Animation::PlayFrame::IsFrameDone()
{
	if (targetTime <= timer) { return true; }
	else { return false; }
};

void DOG::Animation::PlayFrame::ResetTime()
{
	timer = 0;
};

int DOG::Animation::PlayFrame::GetFrameNum()
{
	return frame;
};

DOG::Animation::Loop::Loop(int loopToIndex)
	: loopToIndex(loopToIndex) {}

int DOG::Animation::Loop::GetLoopToIndex()
{
	return loopToIndex;
};