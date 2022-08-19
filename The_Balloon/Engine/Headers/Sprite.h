/*
File Name: Sprite.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include <string>
#include <filesystem> 
#include "Texture.h"
namespace DOG {
    class Texture;
    class Animation;
}

namespace DOG {
    class Sprite {
    public:
        Sprite();
        ~Sprite();

        void PlayAnimation(int anim);
        void Update(double dt);
        bool IsAnimationDone();
        int GetAnimationIndex();
        void Load(const std::filesystem::path& spriteInfoFile);
        void Draw(math::vec2 location ,bool flip);
        void Draw(math::vec2 location, int index);

        math::ivec2 GetHotSpot(int index);
        math::ivec2 GetFrameSize() const;
        math::ivec2 frameSize;
    private:
        math::ivec2 GetFrameTexel(int frameNum) const;


        int currAnim;
        std::vector<Animation*> animations;

        Texture* texturePtr;
        std::vector<math::ivec2> frameTexel;
        std::vector<math::ivec2> hotSpotList;

    };
}