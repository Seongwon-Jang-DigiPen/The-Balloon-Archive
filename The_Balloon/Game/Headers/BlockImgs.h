/*
File Name: BlockImgs.h
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include <vector>
#include "doodle/doodle.hpp"

class BlockImg {
public:
	BlockImg() {
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile1.png"});
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile2.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile3.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile4.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile5.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile6.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile7.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile8.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile9.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile10.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile11.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile12.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile13.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile14.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile15.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile16.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile17.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile18.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile19.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile20.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile21.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile22.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile23.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile24.png" });

		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile25.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile26.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile27.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile28.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile29.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile30.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile31.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile32.png" });
		imgs.push_back(new doodle::Image{ "Assets/Tiles/tiles/tile33.png" });
	}
	doodle::Image* GetImg(int index) { return imgs[index]; }
private:
	std::vector<doodle::Image*> imgs;

};
