/*
File Name: GameMap.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang, Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "Objects.h"
#include "BlockImgs.h"
#include <vector>
#include <string>

#include "../../Engine/Headers/Engine.h"

namespace DOG {
	class Camera;
}

class GameMap {
private:
	using TilePointer = Object::Base*;
	friend class MapEditor;
	friend class SaveManager;

public:
	GameMap();
	~GameMap() {}
	void SetMapDir(std::string dir_name);
	void SetMapDir(std::wstring dir_name);
	void Update(double dt, double scalemat, math::ivec2 campos);

	void Draw0(double scaleamt, const DOG::Camera& cam, bool isConfig);
	void Draw1(double scaleamt, const DOG::Camera& cam, bool isConfig);

	// void Draw(double scaleamt, const DOG::Camera& cam, bool isConfig, void (*p)());

	void Unload();
	bool* getRedBlue() { return &RedBlue; }

	void SetChapter(int chapter2) { stage = chapter2; }

	std::vector<GameMap::TilePointer> GetTiles();
	std::vector<TilePointer> GetAreas();

	class MapChunk {
	private:
		friend class MapEditor;
		friend class GameMap;
		friend class SaveManager;
	public:
		MapChunk();
		MapChunk(std::string _path);
		MapChunk(std::wstring _path);
		~MapChunk()
		{}
		bool IsPlaced(math::ivec2 index_pos);
		bool IsEmpty();
		void Unload();

		static constexpr int size_c = 16;
	private:
		void place_tile(TilePointer t);

		void Update(double dt);
		void DrawB(double scale, const DOG::Camera& cam); 
		void DrawF(double scale, const DOG::Camera& cam);
		void Load();
		void WLoad();

		std::vector<TilePointer> tiles;
		bool grid_placed[size_c * size_c] = { false };
		std::string path;
		std::wstring wPath;
		math::ivec2 map_index; // exact position for GameMap arr
		int arr_index; // arr number for GameMap

		static TilePointer GetTile(Object::Type sel, std::vector<math::ivec2> ivecs = { {0, 0}, {0, 0} });
	};

	struct DIR {
		enum dir {
			CURRENT, LEFT, RIGHT, UP, DOWN, Count
		};
	};
	
	static constexpr int map_width_i = 10;
	static constexpr int map_height_i = 8;

	static constexpr math::ivec2 ChunckSize{ map_width_i, map_height_i };
	bool loadfinished = false;

	void SetRedblue(bool set) { RedBlue = set; }
private:

	void DrawImgTile(double scaleamt, const DOG::Camera& cam);
	void DrawAreas(double scaleamt, const DOG::Camera& cam);
	void render_chunks();
	void Print_Chunks();

	void load_areas(std::string file_name);
	void load_areas(std::wstring file_name);
	void load_images(std::string file_name);

	BlockImg block_image;
	
	void load_images(std::wstring file_name);

	std::vector<MapChunk> whole_m;
	std::vector<MapChunk*> using_m;

	std::vector<TilePointer> bg_texures;
	std::vector<TilePointer> areas;

	MapChunk empty_map;

	math::ivec2 old_index;
	math::ivec2 curr_index;
	int curr_arri = 0;

	DOG::Input key = DOG::Input::Keyboard::Tilde;
	bool view_chunks = false;
	double timer = 1;
	double cls_t = timer;
	bool RedBlue = false;
	int stage = 1;
};