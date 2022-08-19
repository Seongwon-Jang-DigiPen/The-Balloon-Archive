/*
File Name: Texture.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#pragma once
#include <doodle/image.hpp>
#include "Vec2.h"

namespace DOG {
    class Texture {
        friend class TextureManager;
    public:
        Texture();
        Texture(const std::filesystem::path& filePath);
        void Load(const std::filesystem::path& filePath);
        void Draw(math::vec2 location);
        void Draw(math::ivec2 location1, math::ivec2 location2);
        void Draw(math::vec2 location, math::ivec2 texelPos, math::ivec2 frameSize);
        void Draw(math::vec2 location, math::ivec2 texelPos, math::ivec2 frameSize, bool flip);
        bool GetHasLoaded() { return hasLoaded; };

        std::string GetPath() { return path; }

        math::ivec2 GetSize();
    private:
        bool hasLoaded;
        doodle::Image image;   
        std::string path;
    };
}