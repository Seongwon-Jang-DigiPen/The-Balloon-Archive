/*
File Name: MapEditor.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "../../Engine/Headers/Engine.h"
#include "../../Engine/Headers/Vec2.h"
#include "../../Engine/Headers/texture.h"
#include "../../Engine/Headers/Sound.h"
#include "Objects.h"
#include "GameMap.h"
#include "BlockImgs.h"

#include <vector>
#include <doodle/doodle.hpp>

namespace DOG { class Camera; }

class MapEditor 
{
private:
	friend class SaveManager;
	
	using Tile = Object::Base;
	using TilePointer = Object::Base*;
	using TileChunk = GameMap::MapChunk;

	static constexpr int TilePixel = static_cast<int>(Object::Block::size); // pixels of a single square tile
	static constexpr int ChunkPixel = TilePixel * GameMap::MapChunk::size_c; // pixels of a single square chunk
	static constexpr math::ivec2 MapPixel = math::ivec2{ GameMap::ChunckSize } * ChunkPixel; // pixels of each width and height of whole map

	static constexpr int TileNumber = GameMap::MapChunk::size_c; // numbers of tiles for each row and column in one chunk
	static constexpr int ChunkNumber = GameMap::ChunckSize.x * GameMap::ChunckSize.y; // numbers of chuncks for each row and column in whole map

public:
	MapEditor();

	void Update();
	void DrawStatic();
	void DrawDynamic();
	void UnLoad();
	void EditWith(GameMap& map);
	void SetCamera(DOG::Camera* cam);
	void Load();
	bool IsConfigurating();
	void SetChapter(int chapter2) { currentChapter = chapter2; }
	math::ivec2 GetMousePos();

	double scale_amt;

	enum class Menu { 
		Mouse, Block, Area, Enemy, Item, Image, Save, Load, Clear, Size 
	};

private:

	std::vector<math::ivec2> temp_tile_datas;

	std::vector<math::irect2> lines;
	std::vector<DOG::Button> menu_buttons;

	std::vector<std::vector<DOG::Button>> button_list;

	std::vector<std::string> file_list;
	std::vector<DOG::Button> file_buttons;

	std::vector<DOG::Texture*> textures;

	void update_edit_win();
	void update_fname_input();
	void update_fselect_win();

	void load_fnames();
	void check_editBar();
	void save_map();
	void clear_map();
	void place_plant(TileChunk& chunk, TilePointer t);
	void image_tile_setup();

	DOG::Input editKey, backspace, enter , normal_inc, normal_dec;
	DOG::Input test = DOG::Input::Keyboard::_1;
	std::string save_dir_name;

	Object::Type s_type;
	Menu sel_menu;
	BlockImg block_image;

	bool isKeyPressed;
	bool isMousePressed;
	bool isEditing;
	bool isSelectingFile;
	bool isReadytoSave;
	bool isMenuOpened;
	bool isDragging;
	int currentChapter = 1;
	int Normal_num = 0;
	int image_selected = 0;

	GameMap* map;
	DOG::Camera* camera;
};