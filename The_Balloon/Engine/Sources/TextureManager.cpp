/*
File Name: TextureManager.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#pragma once
#include "../Headers/Engine.h"
#include "../Headers/TextureManager.h"
#include "../Headers/Texture.h"

DOG::Texture* DOG::TextureManager::Load(const std::filesystem::path& filePath)
{
	if (pathToTexture.find(filePath) == pathToTexture.end())
	{
		pathToTexture.insert(std::pair<std::filesystem::path, DOG::Texture*>(filePath, new DOG::Texture(filePath)));
	}
	return pathToTexture[filePath];
}

void DOG::TextureManager::Unload()
{
	Engine::getLogger().LogEvent("Clear Textures");

	for (std::pair<std::filesystem::path, DOG::Texture*> pair : pathToTexture)
	{
		delete pair.second;
	}
	pathToTexture.clear();
}