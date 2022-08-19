/*
File Name: Texture.cpp
Project Name: The balloon
Author(s)
Main: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include <doodle/drawing.hpp>
#include "../Headers/Texture.h"
#include <iostream>

DOG::Texture::Texture() : hasLoaded(false) {}
DOG::Texture::Texture(const std::filesystem::path& filePath) : hasLoaded(false) 
{
	path = filePath.string();
	image = doodle::Image{ filePath };
};

void DOG::Texture::Load(const std::filesystem::path& filePath) {
	path = filePath.string();
	image = doodle::Image{ filePath };
	hasLoaded = true;
}

void DOG::Texture::Draw(math::vec2 location) {
	doodle::draw_image(image, location.x, location.y);
}
void DOG::Texture::Draw(math::ivec2 location1, math::ivec2 location2)
{
	doodle::draw_image(image, location1.x, location1.y, location2.x, location2.y);
}

void DOG::Texture::Draw(math::vec2 location, math::ivec2 texelPos, math::ivec2 frameSize) {
	doodle::push_settings();
	doodle::apply_translate(location.x, location.y);
	doodle::draw_image(image, 0, 0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
	doodle::pop_settings();
}

void DOG::Texture::Draw(math::vec2 location, math::ivec2 texelPos, math::ivec2 frameSize, bool flip)
{
	doodle::push_settings();
	doodle::apply_translate(location.x, location.y);
	if (flip == true)
	{		
		doodle::apply_scale(-1.0,1);
		doodle::draw_image(image, -static_cast<double>(frameSize.x),0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
	}
	else {
		doodle::draw_image(image, 0,0, static_cast<double>(frameSize.x), static_cast<double>(frameSize.y), texelPos.x, texelPos.y);
	}
	doodle::pop_settings();
}

math::ivec2 DOG::Texture::GetSize() { return { image.GetWidth(), image.GetHeight() }; }