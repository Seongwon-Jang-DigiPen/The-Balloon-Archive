/*
File Name: TextureManager.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include <filesystem>
#include <map>

namespace DOG {
    class Texture;

    class TextureManager {
    public:
        Texture* Load(const std::filesystem::path& filePath);
        void Unload();

    private:
        std::map<std::filesystem::path, Texture*> pathToTexture;
    };
}