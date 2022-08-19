/*
File Name: GameMap.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Seongwon Jang, Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/GameMap.h"
#include "../../Engine/Headers/Engine.h"
#include "../../Engine/Headers/Camera.h"
#include <doodle/drawing.hpp> // translate
#include <fstream>
#include <io.h> // finddata
#include <algorithm> // find
#include <iostream> // cout

GameMap::GameMap()
{}

void GameMap::SetMapDir(std::wstring dir_name)
{
	whole_m.clear();

	std::wstring searching = Engine::getSaveManager().Get_MapDirPath() + L'/' + dir_name + L"/*.txt";
	std::vector<std::wstring> names; // this will contain the list of files' path

	// take list of files from folder
	//_finddata_t find;
	//auto handle = _findfirst(searching.c_str(), &find);

	WIN32_FIND_DATA find;
	auto handle = ::FindFirstFile(searching.c_str(), &find);

	if (handle == INVALID_HANDLE_VALUE)
		return;

	wchar_t nm[260] = L"empty_map.txt";
	wchar_t area[32] = L"area_datas.txt";
	wchar_t bgtex[32] = L"bg_textures.txt";

	int result = 0;
	do
	{
		if (std::wcscmp(find.cFileName, nm) != 0 && std::wcscmp(find.cFileName, area) != 0 && std::wcscmp(find.cFileName, bgtex) != 0)
			names.push_back(find.cFileName); // it automatically sorts

	} while (::FindNextFile(handle, &find));

	::FindClose(handle);

	std::sort(names.begin(), names.end()); // to make sure be sorted

	std::wstring member_dirn = dir_name;
	for (std::wstring file_name : names) {
		std::wstring path = member_dirn + L"/" + file_name;
		whole_m.push_back(path); // pushed back in order as a chunk
	}

	for (MapChunk& d : whole_m)
	{
		d.WLoad(); // chunck load
	}

	load_areas(dir_name);
	load_images(dir_name);

	curr_index = { 0, 0 };
	render_chunks();


	system("cls");
	for (MapChunk& d : whole_m)
		for (TilePointer& t : d.tiles) {
			if (t->GetType() == Object::Type::Normal) {
				Object::Normal* normal = static_cast<Object::Normal*>(t);
				normal->SetStage(stage);
			}
			t->SetSprite(&block_image);
		}

	loadfinished = true;
}

void GameMap::SetMapDir(std::string dir_name)
{
	whole_m.clear();

	std::string searching = "Assets/maps/" + dir_name + "/*.txt";
	std::vector<std::string> names; // this will contain the list of files' path

	// take list of files from folder
	_finddata_t find;
	auto handle = _findfirst(searching.c_str(), &find);

	if (handle == -1)
		return;

	char nm[260] = "empty_map.txt";
	char area[32] = "area_datas.txt";
	char bgtex[32] = "bg_textures.txt";

	int result = 0;
	do
	{
		if (std::strcmp(find.name, nm) != 0 && std::strcmp(find.name, area) != 0 && std::strcmp(find.name, bgtex) != 0)
			names.push_back(find.name); // it automatically sorts

		result = _findnext(handle, &find);
	} while (result != -1);

	_findclose(handle);

	std::sort(names.begin(), names.end()); // to make sure be sorted

	std::string member_dirn = dir_name;
	for (std::string file_name : names) {
		std::string path = member_dirn + "/" + file_name;
		whole_m.push_back( path ); // pushed back in order as a chunk
	}

	for (MapChunk& d : whole_m)
	{
		d.Load(); // chunck load
	}

	load_areas(dir_name);
	load_images(dir_name);

	curr_index = { 0, 0 };
	render_chunks();

	system("cls");
	for (MapChunk& d : whole_m)
		for (TilePointer& t : d.tiles) {
			if (t->GetType() == Object::Type::Normal) {
				Object::Normal* normal = static_cast<Object::Normal*>(t);
				normal->SetStage(stage);
			}
			t->SetSprite(&block_image);
		}

	loadfinished = true;
}

void GameMap::Update(double dt, double scalemat, math::ivec2 pos)
{
	int block_size = static_cast<int>(Object::Block::size);
	int offset = static_cast<int>(block_size * MapChunk::size_c * scalemat);

	old_index = curr_index;
	curr_index = { pos.x / offset, pos.y / offset };
	curr_arri = map_width_i * curr_index.y + curr_index.x;

	curr_index.x = std::clamp(curr_index.x, 0, ChunckSize.x - 1);
	curr_index.y = std::clamp(curr_index.y, 0, ChunckSize.y - 1);

	//Engine::getLogger().LogDebug(std::to_string(r_i.x) + '\t' + std::to_string(r_i.y));

	for (MapChunk* d : using_m) {
		d->Update(dt);

		for (TilePointer info : d->tiles) {
			if (info->GetType() == Object::Type::Button)
			{
				Object::Button* button = static_cast<Object::Button*>(info);
				button->SetRedblue(RedBlue);
			}
			if (info->GetType() == Object::Type::Red)
			{
				Object::Red* red = static_cast<Object::Red*>(info);
				red->SetRedblue(RedBlue);
			}
			if (info->GetType() == Object::Type::Blue)
			{
				Object::Blue* blue = static_cast<Object::Blue*>(info);
				blue->SetRedblue(RedBlue);
			}
			if (info->GetType() == Object::Type::Normal)
			{
				Object::Normal* normal = static_cast<Object::Normal*>(info);
				normal->SetStage(stage);
			}
			
		}
	}

	for (TilePointer a : areas) {
		a->Update(dt);
	}

	if (old_index != curr_index)
		render_chunks();

	if (key.IsKeyPressed() == true) {
		view_chunks = !view_chunks;
		if (!view_chunks)
			system("cls"), std::cout << "Chunk view OFF" << std::endl;
	}

	if (cls_t > 0)
		cls_t -= dt;
	if (view_chunks && cls_t < dt)
		Print_Chunks(), cls_t = timer;
	//Engine::getLogger().LogDebug("camera is in area " + std::to_string(indexes.y));
}

void GameMap::Draw0(double scaleamt, const DOG::Camera& cam, bool isConfig) {
	DrawImgTile(scaleamt, cam);

	if (isConfig == true)
		for (MapChunk& w : whole_m)
			w.DrawB(scaleamt, cam);
	else
		for (MapChunk* u : using_m)
			u->DrawB(scaleamt, cam);

}

void GameMap::Draw1(double scaleamt, const DOG::Camera& cam, bool isConfig) {

	DrawAreas(scaleamt, cam);

	if (isConfig == true)
		for (MapChunk& w : whole_m)
			w.DrawF(scaleamt, cam);
	else
		for (MapChunk* u : using_m)
			u->DrawF(scaleamt, cam);
}

//void GameMap::Draw(double scaleamt, const DOG::Camera& cam, bool isConfig, void (*drawPrince)())
//{
//	DrawImgTile(scaleamt, cam);
//
//	if (isConfig == true)
//		for (MapChunk& w : whole_m)
//			w.DrawB(scaleamt, cam);
//	else
//		for (MapChunk* u : using_m)
//			u->DrawB(scaleamt, cam);
//
//	DrawAreas(scaleamt, cam);
//
//	drawPrince();
//
//	if (isConfig == true)
//		for (MapChunk& w : whole_m)
//			w.DrawF(scaleamt, cam);
//	else
//		for (MapChunk* u : using_m)
//			u->DrawF(scaleamt, cam);
//}

void GameMap::DrawImgTile(double scaleamt, const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scaleamt, scaleamt);

	for (TilePointer t : bg_texures)
		t->Draw();

	doodle::pop_settings();
}

void GameMap::DrawAreas(double scaleamt, const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scaleamt, scaleamt);

	for (TilePointer a : areas)
		a->Draw();

	doodle::pop_settings();
}

void GameMap::Print_Chunks()
{
	system("cls");
	std::cout << "Chunk view ON" << std::endl;

	bool barr[map_height_i * map_width_i] = { false };
	for (MapChunk* id : using_m)
		if (id->arr_index >= 0)
			barr[id->arr_index] = true;

	std::cout << '\n';
	std::cout << "==================" << std::endl;
	for (int j = map_height_i - 1; j >= 0; j--) {
		for (int i = 0; i < map_width_i; i++) {
			std::string c = ". ";
			int a = map_width_i * j + i;
			if (barr[a]) c = "# ";
			std::cout << c;
		}
		std::cout << '\n';
	}

	std::cout << '\n';
	std::cout << "chunks size : " + std::to_string(static_cast<int>(using_m.size())) << std::endl;

	std::string s = "chunks index : ";
	for (MapChunk* t : using_m)
		s += std::to_string(t->arr_index) + " ";

	std::cout << s << std::endl;
}

void GameMap::load_areas(std::string d_name)
{
	std::ifstream area_file;
	area_file.open("Assets/maps/" + d_name + "/area_datas.txt");

	if (area_file.is_open()) {

		std::cout << "Start Loading area..." << std::endl;

		while (!area_file.eof())
		{
			std::string name;
			area_file >> name;

			if (name == "") break;

			int itype = 0; area_file >> itype;

			std::vector<math::ivec2> ivecs = { { 0, 0 }, { 0, 0 } };

			area_file >> ivecs[0].x; area_file >> ivecs[0].y;
			area_file >> ivecs[1].x; area_file >> ivecs[1].y;

			areas.push_back(MapChunk::GetTile(static_cast<Object::Type>(itype), ivecs));
		}
	}
	else
		throw std::runtime_error("no area data exist");

	std::cout << "Area load completed" << std::endl;

	area_file.close();
}

void GameMap::load_areas(std::wstring file_name)
{
	std::ifstream area_file;
	area_file.open(Engine::getSaveManager().Get_MapDirPath() + L'/' + file_name + L"/area_datas.txt");

	if (area_file.is_open()) {

		std::cout << "Start Loading area..." << std::endl;

		while (!area_file.eof())
		{
			std::string name;
			area_file >> name;

			if (name == "") break;

			int itype = 0; area_file >> itype;

			std::vector<math::ivec2> ivecs = { { 0, 0 }, { 0, 0 } };

			area_file >> ivecs[0].x; area_file >> ivecs[0].y;
			area_file >> ivecs[1].x; area_file >> ivecs[1].y;

			areas.push_back(MapChunk::GetTile(static_cast<Object::Type>(itype), ivecs));
		}
	}
	else
		throw std::runtime_error("no area data exist");

	std::cout << "Area load completed" << std::endl;

	area_file.close();
}


void GameMap::load_images(std::string file_name)
{
	std::ifstream img_file;
	img_file.open("Assets/maps/" + file_name + "/bg_textures.txt");

	if (img_file.is_open()) {

		std::cout << "Start loading images.." << std::endl;

		while (!img_file.eof())
		{
			std::string name;
			img_file >> name;

			if (name == "") break;

			int itype; img_file >> itype;
			Object::Type type = static_cast<Object::Type>(itype);

			std::vector<math::ivec2> ivecs = { { 0, 0 }, { 0, 0 } };

			img_file >> ivecs[0].x;
			img_file >> ivecs[0].y;

			std::string texture_path;
			img_file >> texture_path;

			TilePointer t = MapChunk::GetTile(type, ivecs);
			Object::Image* i = static_cast<Object::Image*>(t);

			i->SetImage(new DOG::Texture{ texture_path });

			bg_texures.push_back(i);

		}
	}
	else
		throw std::runtime_error("no image tile data exist");

	std::cout << "image load completed" << std::endl;

	img_file.close();
}

void GameMap::load_images(std::wstring file_name)
{
	std::ifstream img_file;
	img_file.open(Engine::getSaveManager().Get_MapDirPath() + L'/' + file_name + L"/bg_textures.txt");

	if (img_file.is_open()) {

		std::cout << "Start loading images.." << std::endl;

		while (!img_file.eof())
		{
			std::string name;
			img_file >> name;

			if (name == "") break;

			int itype; img_file >> itype;
			Object::Type type = static_cast<Object::Type>(itype);

			std::vector<math::ivec2> ivecs = { { 0, 0 }, { 0, 0 } };

			img_file >> ivecs[0].x;
			img_file >> ivecs[0].y;

			std::string texture_path;
			img_file >> texture_path;

			TilePointer t = MapChunk::GetTile(type, ivecs);
			Object::Image* i = static_cast<Object::Image*>(t);

			i->SetImage(new DOG::Texture{ texture_path });

			bg_texures.push_back(i);

		}
	}
	else
		throw std::runtime_error("no image tile data exist");

	std::cout << "image load completed" << std::endl;

	img_file.close();
}




void GameMap::Unload()
{
	
	for (MapChunk& f : whole_m) // pointer copied also in using_m
	{
		f.Unload();
		f.tiles.clear();
	}

	for (TilePointer a : areas)
		delete a;

	for (TilePointer t : bg_texures)
		delete t;

	whole_m.clear();
	using_m.clear();
	RedBlue = false;
	areas.clear();
	bg_texures.clear();
}

std::vector<GameMap::TilePointer> GameMap::GetTiles()
{
	std::vector<TilePointer> tile_t;

	for (MapChunk* c : using_m)
		for (TilePointer t : c->tiles)
			tile_t.push_back(t);

	return tile_t;
}

std::vector<GameMap::TilePointer> GameMap::GetAreas()
{
	return areas;
}

void GameMap::render_chunks()
{
	int curri = map_width_i * curr_index.y + curr_index.x;
	int R = curri + 1, L = curri - 1;
	int U = curri + map_width_i, D = curri - map_width_i;

	int UR = R + map_width_i, UL = L + map_width_i;
	int DR = R - map_width_i, DL = L - map_width_i;
	using_m.clear();

	curri = std::clamp(curri, 0, map_width_i * map_height_i);

	using_m.push_back(&whole_m[curri]);

	if (curr_index.x < map_width_i - 1)
		using_m.push_back(&whole_m[R]);

	if (curr_index.x > 0)
		using_m.push_back(&whole_m[L]);

	if (curr_index.y < map_height_i - 1) {
		using_m.push_back(&whole_m[U]);

		if (curr_index.x < map_width_i - 1)
			using_m.push_back(&whole_m[UR]);

		if (curr_index.x > 0)
			using_m.push_back(&whole_m[UL]);
	}

	if (curr_index.y > 0) {
		using_m.push_back(&whole_m[D]);

		if (curr_index.x < map_width_i - 1)
			using_m.push_back(&whole_m[DR]);

		if (curr_index.x > 0)
			using_m.push_back(&whole_m[DL]);
	}

}

GameMap::MapChunk::MapChunk() : arr_index(-1) { }

GameMap::MapChunk::MapChunk(std::string _path) : path(_path) { }

GameMap::MapChunk::MapChunk(std::wstring _path) : wPath(_path) {}



void GameMap::MapChunk::Load()
{
	std::string input_path = "Assets/maps/" + path;

	std::ifstream map_file;
	map_file.open(input_path);
	if (map_file.is_open() == true)
	{
		map_file >> map_index.y;
		map_file >> map_index.x;
		arr_index = map_width_i * map_index.y + map_index.x;

		Object::Plant* plant = nullptr;
		while (!map_file.eof())
		{
			std::string name;
			map_file >> name;
			if (name == "") return;

			//system("cls");
			//std::cout << "Placing " + name + " block..." << std::endl;

			int ty_int = 0; map_file >> ty_int;
			Object::Type type = static_cast<Object::Type>(ty_int);

			std::vector<math::ivec2> ivecs = { { 0, 0 }, { 0, 0 } };
			map_file >> ivecs[0].x;
			map_file >> ivecs[0].y;

			if (type < Object::Type::Count)
				if (GetTile(type)->par_num() == 2) {
					map_file >> ivecs[1].x;
					map_file >> ivecs[1].y;
				}
			TilePointer tpr = nullptr;

			if (type < Object::Type::Count)
				tpr = GetTile(type, ivecs);

			
			if (type == Object::Type::Plant)
				plant = static_cast<Object::Plant*>(tpr);

			
			if (plant != nullptr) {
				if (type == Object::Type::Stem) {
					tiles.push_back(new Object::Plant::Stem{ plant, ivecs.front() });
				}
				
				if (type == Object::Type::Leaf) {
					tiles.push_back(new Object::Plant::Leaf{ plant, ivecs.front() });
				}
			}

			if (type < Object::Type::Count)
			{
				place_tile(tpr);
			}
		}

	}
	else
	{
		throw std::runtime_error("Failed to Load!");
	}
}

void GameMap::MapChunk::WLoad()
{
	std::wstring input_path = Engine::getSaveManager().Get_MapDirPath() + L'/' + wPath;

	std::ifstream map_file;
	map_file.open(input_path);
	if (map_file.is_open() == true)
	{
		map_file >> map_index.y;
		map_file >> map_index.x;
		arr_index = map_width_i * map_index.y + map_index.x;

		Object::Plant* plant = nullptr;
		while (!map_file.eof())
		{
			std::string name;
			map_file >> name;
			if (name == "") return;

			//system("cls");
			//std::cout << "Placing " + name + " block..." << std::endl;

			int ty_int = 0; map_file >> ty_int;
			Object::Type type = static_cast<Object::Type>(ty_int);

			std::vector<math::ivec2> ivecs = { { 0, 0 }, { 0, 0 } };
			map_file >> ivecs[0].x;
			map_file >> ivecs[0].y;

			if (type < Object::Type::Count)
				if (GetTile(type)->par_num() == 2) {
					map_file >> ivecs[1].x;
					map_file >> ivecs[1].y;
				}
			TilePointer tpr = nullptr;

			if (type < Object::Type::Count)
				tpr = GetTile(type, ivecs);


			if (type == Object::Type::Plant)
				plant = static_cast<Object::Plant*>(tpr);


			if (plant != nullptr) {
				if (type == Object::Type::Stem) {
					tiles.push_back(new Object::Plant::Stem{ plant, ivecs.front() });
				}

				if (type == Object::Type::Leaf) {
					tiles.push_back(new Object::Plant::Leaf{ plant, ivecs.front() });
				}
			}

			if (type < Object::Type::Count)
			{
				place_tile(tpr);
			}
		}

	}
	else
	{
		throw std::runtime_error("Failed to Load!");
	}
}


void GameMap::MapChunk::DrawB(double scale, const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scale, scale);

	for (TilePointer& info : tiles)
		if (info->shouldDrawnBehind() == true)
			info->Draw();

	doodle::pop_settings();
}

void GameMap::MapChunk::DrawF(double scale, const DOG::Camera& cam)
{
	doodle::push_settings();
	doodle::apply_translate(-cam.GetPosition().x, -cam.GetPosition().y);
	doodle::apply_scale(scale, scale);

	for (TilePointer& info : tiles)
		if (info->shouldDrawnBehind() == false)
			info->Draw();

	doodle::pop_settings();
}

void GameMap::MapChunk::place_tile(TilePointer t)
{

	tiles.push_back(t);

	math::ivec2 map_off = map_index * (int)Object::Block::size * size_c;

	math::ivec2 grid_vec = (t->GetInitPos() - map_off) / (int)Object::Block::size;

	if (size_c * grid_vec.y + grid_vec.x > 256)
	{
		Engine::getLogger().LogError("///////////////////////////////////");
		Engine::getLogger().LogError("grid_placed error");
		Engine::getLogger().LogError("grid_vec.x: " + std::to_string(t->GetInitPos().x));
		Engine::getLogger().LogError("grid_vec.y: " + std::to_string(t->GetInitPos().y));
		Engine::getLogger().LogError("grid_vec.x: " + std::to_string(grid_vec.x));
		Engine::getLogger().LogError("grid_vec.y: " + std::to_string(grid_vec.y));
		Engine::getLogger().LogError("file path: " + path);
		Engine::getLogger().LogError("tile: " + t->GetName());
		Engine::getLogger().LogError("///////////////////////////////////");
	}
	else
	{
		grid_placed[size_c * grid_vec.y + grid_vec.x] = true;
	}

}

void GameMap::MapChunk::Update(double dt)
{
	int index_ = 0;
	for (TilePointer& info : tiles)
	{
		info->Update(dt);

		if (info->isItem() == true && info->GetType() == Object::Type::Helium) {
			Object::Helium* helium_t = static_cast<Object::Helium*>(info);

			if (helium_t->wasTaken() == true) {
				tiles.erase(tiles.begin() + index_);
				grid_placed[size_c * info->GetInitPos().y + info->GetInitPos().x] = false;
			}
		}
		else if (info->GetType() == Object::Type::Stem) {
			Object::Plant::Stem* s = static_cast<Object::Plant::Stem*>(info);
			if (s->GetOrigin() == nullptr) {
				tiles.erase(tiles.begin() + index_);
			}
		}
		else if (info->GetType() == Object::Type::Leaf) {
			Object::Plant::Leaf* l = static_cast<Object::Plant::Leaf*>(info);
			if (l->GetOrigin() == nullptr)
				tiles.erase(tiles.begin() + index_);
		}

		index_++;
	}
}

bool GameMap::MapChunk::IsPlaced(math::ivec2 index_pos)
{
	return grid_placed[size_c * index_pos.y + index_pos.x];
}

bool GameMap::MapChunk::IsEmpty() { return tiles.empty(); }

void GameMap::MapChunk::Unload()
{
	for (TilePointer p : tiles) {
		delete p;
	}

	for (bool& b : grid_placed)
		b = false;

	tiles.clear();
}

GameMap::TilePointer GameMap::MapChunk::GetTile(Object::Type sel, std::vector<math::ivec2> ivecs)
{
	using namespace Object;
	std::vector <math::ivec2> v_t;
	v_t.resize(3);

	for (int i = 0; i < ivecs.size(); i++) {
		v_t[i] = ivecs[i];
	}

	math::ivec2 pos1 = v_t[0];
	math::ivec2 pos2 = v_t[1];

	switch (sel)
	{
	case Type::None: return new Base();  break;
	case Type::Block: return new Block(); break;
	case Type::Area: return new Area(); break;
	case Type::Enemy: return new Enemy_base(); break;
	case Type::Item: return new Item(); break;
	case Type::Normal: return new Normal(pos1, pos2); break;
	case Type::Moving: return new Moving(pos1, pos2); break;
	case Type::OnOff: return new OnOff(pos1, pos2); break;
	case Type::Puddle: return new Puddle(pos1); break;
	case Type::Furry: return new Furry(pos1); break;
	case Type::Plant: return new Plant(pos1, pos2); break;
	case Type::Absorb: return new Absorber(pos1); break;
	case Type::Spike: return new Spike(pos1); break;
	case Type::Button: return new Button(pos1); break;
	case Type::Red: return new Red(pos1); break;
	case Type::Blue: return new Blue(pos1); break;
	case Type::Wind: return new Wind(pos1, pos2); break;
	case Type::Water: return new Water(pos1, pos2); break;
	case Type::Pinny: return  new Pinny(pos1, pos2); break;
	case Type::MrCloudy: return new Cloudy(pos1, pos2); break;
	case Type::Robot: return new Robot(pos1, pos2); break;
	case Type::Helium: return new Helium(pos1); break;
	case Type::Candy: return new Candy(pos1); break;
	case Type::UP_1: return new UP1(pos1); break;
	case Type::Image: return new Image(pos1); break;
	case Type::Count: 
	case Type::Stem:
	case Type::Leaf:
	default:
	return new Base();
	}
}