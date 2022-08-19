/*
File Name: MapEditor.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
Sub: Sehun Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/MapEditor.h"
#include "../../Engine/Headers/Engine.h"
#include "doodle/input.hpp"
#include "doodle/drawing.hpp"
#include "../../Engine/Headers/Camera.h"
#include "../Headers/Objects.h"

#include <fstream>
#include <direct.h> // _mkdir

MapEditor::MapEditor()
	: editKey(DOG::Input::Keyboard::F5), backspace(DOG::Input::Keyboard::BSpace), enter(DOG::Input::Keyboard::Enter), normal_inc(DOG::Input::Keyboard::Plus), normal_dec(DOG::Input::Keyboard::Subt),
	isKeyPressed(false), isEditing(false), isSelectingFile(false), isReadytoSave(false), isMenuOpened(false), s_type(Object::Type::None), sel_menu(Menu::Size),
	isMousePressed(false), map(nullptr), camera(nullptr), scale_amt(1), isDragging(false), Normal_num(1)
{}

void MapEditor::EditWith(GameMap& par_map) { map = &par_map; }

void MapEditor::SetCamera(DOG::Camera* cam) { camera = cam; };

void MapEditor::image_tile_setup() { // add images to use as background
	textures.push_back(new DOG::Texture("Assets/img_tiles/image0.png"));
	textures.push_back(new DOG::Texture("Assets/img_tiles/img_tile1.png"));
	textures.push_back(new DOG::Texture("Assets/img_tiles/img_tile2.png"));
	textures.push_back(new DOG::Texture("Assets/img_tiles/img_tile3.png"));
	textures.push_back(new DOG::Texture("Assets/img_tiles/img_tile3_1chunk.png"));

	textures.push_back(new DOG::Texture("Assets/img_tiles/sign_elec_interact.png"));
	textures.push_back(new DOG::Texture("Assets/img_tiles/sign_elec_whatcando.png"));
	textures.push_back(new DOG::Texture("Assets/img_tiles/sign_water_interact.png"));
	textures.push_back(new DOG::Texture("Assets/img_tiles/sign_water_whatcando.png"));
	textures.push_back(new DOG::Texture("Assets/img_tiles/sign_water_toplant.png"));
}

void MapEditor::Load()
{
	if (camera == nullptr)
		throw std::runtime_error("unexpected camera for map editor");

	std::vector<std::string> b_tex = { "Nomal.png", "Move.png", "OnOff.png", "Nomal.png", "furry.png", "plant.png", "Nomal.png", "spike.png", "Nomal.png", "Nomal.png", "Nomal.png" };
	std::vector<std::string> a_tex = { "wind.png", "water.png" };
	std::vector<std::string> e_tex = { "pinny.png", "cloudy.png", "scrap.png" };
	std::vector<std::string> i_tex = { "helium.png", "candy.png", "UP_1.png" };

	image_tile_setup();

	std::vector<std::string> Menu_Tex = { "cursor.png", "Nomal.png", "wind.png", "pinny.png", "candy.png", "images.png", "Save.png", "Load.png", "Reset.png" };

	int wind2 = Engine::getWindow().GetSize().x / 3;
	int yoffset1 = Engine::getWindow().GetSize().y - (DOG::Button::size * 2);
	int yoffset2 = Engine::getWindow().GetSize().y - DOG::Button::size;

	std::vector<DOG::Button> b_buttons, a_buttons, e_buttons, i_buttons, img_buttons;

	for (int x = 0; x < static_cast<int>(b_tex.size()); x++)
		b_buttons.push_back(DOG::Button{ { wind2 + x * DOG::Button::size, yoffset1 }, b_tex[x] });
	for (int x = 0; x < static_cast<int>(a_tex.size()); x++)
		a_buttons.push_back(DOG::Button{ { wind2 + x * DOG::Button::size, yoffset1 }, a_tex[x] });
	for (int x = 0; x < static_cast<int>(e_tex.size()); x++)
		e_buttons.push_back(DOG::Button{ { wind2 + x * DOG::Button::size, yoffset1 }, e_tex[x] });
	for (int x = 0; x < static_cast<int>(i_tex.size()); x++)
		i_buttons.push_back(DOG::Button{ { wind2 + x * DOG::Button::size, yoffset1 }, i_tex[x] });
	for (int x = 0; x < static_cast<int>(textures.size()); x++)
		img_buttons.push_back(DOG::Button{ { wind2 + x * DOG::Button::size, yoffset1 }, "images.png" });

	button_list.push_back(b_buttons);
	button_list.push_back(a_buttons);
	button_list.push_back(e_buttons);
	button_list.push_back(i_buttons);
	button_list.push_back(img_buttons);

	for (int x = 0; x < static_cast<int>(Menu::Size); x++)
		menu_buttons.push_back(DOG::Button{ math::ivec2{ wind2 + x * DOG::Button::size, yoffset2}, Menu_Tex[x] });

	s_type = Object::Type::None;

}

void MapEditor::UnLoad()
{
	isKeyPressed = false;
	isEditing = false;
	isSelectingFile = false;
	isReadytoSave = false;
	isMenuOpened = false;
	scale_amt = 1;

	button_list.clear();
	menu_buttons.clear();
	lines.clear();
	file_list.clear();
	file_buttons.clear();

	for (DOG::Texture* tp : textures)
		delete tp;

	textures.clear();
}

void MapEditor::Update()
{
	
	if (editKey.IsKeyPressed() == true && Engine::Reference().CheckdeveloperMode() == true)
	{
		isEditing = !isEditing;
		if (isEditing == true) {
			Engine::getLogger().LogDebug("Editor On");
		}
		else {
			Engine::getLogger().LogDebug("Editor Off");
			camera->SetExtent({ { 0, 0 }, MapPixel });
		}
	}

	if (isEditing == true) {
		update_edit_win();
		if (sel_menu == Menu::Mouse) {
			scale_amt = std::clamp(1 + Engine::getInput().scroll_amount * 0.02, 0.25, 2.0);
		}
		else if (sel_menu == Menu::Block) {
			if (normal_inc.IsKeyReleased()) { Normal_num++; }
			if (normal_dec.IsKeyReleased()) { Normal_num--; }
			Normal_num = std::clamp(Normal_num, 0, 8);
		}
		camera->SetExtent({ { 0, 0 }, {(int)(MapPixel.x * scale_amt), (int)(MapPixel.y * scale_amt)} });
		//scale_amt = std::clamp(scale_amt, 0.15, 1.0);
	}
	else {
		if (scale_amt < 1)
			scale_amt *= 1.02;

		isReadytoSave = false;
		isSelectingFile = false;
	}

	if (isReadytoSave == true) {
		update_fname_input();
	}

	if (isSelectingFile == true) {
		update_fselect_win();
	}
}

math::ivec2 MapEditor::GetMousePos() {
	math::ivec2 camP = camera->Get_iPosition();
	math::ivec2 cammouse = camP + Engine::getInput().GetMousePosition();
	math::vec2 scaled = cammouse / scale_amt;
	return math::ivec2{ static_cast<int>(scaled.x), static_cast<int>(scaled.y) };
}

void MapEditor::update_edit_win()
{
	math::ivec2 winSize = Engine::getWindow().GetSize();

	bool is_selecting_area = Object::AREA_MASK <= static_cast<int>(s_type) && static_cast<int>(s_type) < Object::ENEMY_MASK;

	math::ivec2 map_i = GetMousePos() / ChunkPixel;
	math::ivec2 tile_pos = GetMousePos() / TilePixel * TilePixel;
	math::ivec2 tiles_i = GetMousePos() / TilePixel - map_i * TileChunk::size_c;

	int map_index_x = GameMap::map_width_i * map_i.y + map_i.x;
	map_index_x = std::clamp(map_index_x, 0, ChunkNumber - 1);


	TileChunk& chunk = map->whole_m[map_index_x];
	bool check_grid = chunk.grid_placed[TileChunk::size_c * tiles_i.y + tiles_i.x];

	//if (test.IsKeyPressed()) Engine::getLogger().LogDebug(std::to_string(tiles_i.x) + " " + std::to_string(tiles_i.y));

	int bsize = DOG::Button::size * 2;
	if (Engine::getInput().GetMousePosition().y < winSize.y - bsize)
	{

		if (doodle::MouseIsPressed == true && isReadytoSave == false && isSelectingFile == false)
		{
			if (doodle::MouseButton == doodle::MouseButtons::Left)
			{
				if (sel_menu == Menu::Mouse)
				{
					//isDragging == true;
					math::vec2 move_direction = camera->GetPosition() - Engine::getInput().GetMouseDirection() * 30;
					camera->SetPosition(move_direction);

					if (camera->Get_iPosition().x < 0)
						camera->SetPosition({ 0, camera->GetPosition().y });
					if (camera->Get_iPosition().y < 0)
						camera->SetPosition({ camera->GetPosition().x, 0 });
					if (camera->Get_iPosition().x > MapPixel.x * scale_amt - winSize.x)
						camera->SetPosition({ (double)(MapPixel.x * scale_amt - winSize.x), camera->GetPosition().y });
					if (camera->Get_iPosition().y > MapPixel.y * scale_amt - winSize.y)
						camera->SetPosition({ camera->GetPosition().x, (double)(MapPixel.y * scale_amt - winSize.y) });
				}
				else
				{
					if (is_selecting_area == true)
					{
						if (isMousePressed == false) {
							temp_tile_datas.push_back(GetMousePos());
							Engine::getEffectSound().PlaySounds(8);
							isMousePressed = true;
						}
					}
					else if (s_type != Object::Type::None && check_grid == false)
					{
						if (isMousePressed == false) {
							Engine::getEffectSound().PlaySounds(8);

							temp_tile_datas.push_back(tile_pos);

							if (s_type == Object::Type::Normal) temp_tile_datas.push_back({ Normal_num,currentChapter });

							if (static_cast<int>(temp_tile_datas.size()) == TileChunk::GetTile(s_type)->par_num())
							{
								if (s_type == Object::Type::Plant) temp_tile_datas[1].x = temp_tile_datas.front().x;

								TilePointer temp_tp = TileChunk::GetTile(s_type, temp_tile_datas);

								temp_tp->SetSprite(&block_image);

								if (s_type == Object::Type::Normal) {
									Object::Normal* normal = static_cast<Object::Normal*>(temp_tp);
									normal->SetStage(currentChapter);
								}

								if (s_type == Object::Type::Image) {
									Object::Image* i = static_cast<Object::Image*>(temp_tp);
									i->SetImage(textures[image_selected]);
									map->bg_texures.push_back(temp_tp);
								}
								else {
									chunk.tiles.push_back(temp_tp);
									math::ivec2 sdfawnklsdf = temp_tile_datas.front() - (map_i * ChunkPixel);
									chunk.grid_placed[TileChunk::size_c * sdfawnklsdf.y / TilePixel + sdfawnklsdf.x / TilePixel] = true;
								}

								if (s_type == Object::Type::Plant) place_plant(chunk, temp_tp);

								if (TileChunk::GetTile(s_type)->GetType() != Object::Type::Normal && static_cast<int>(temp_tile_datas.size()) == 2)
									lines.push_back({ temp_tile_datas[0], temp_tile_datas[1] });

								temp_tile_datas.clear();
							}
								isMousePressed = true;
						}
					}

				}
			}

			if (doodle::MouseButton == doodle::MouseButtons::Right)
			{
				if (chunk.tiles.empty() == false && check_grid == true) {
					for (int i = 0; i < static_cast<int>(chunk.tiles.size()); i++) {
						if (chunk.tiles[i]->GetInitPos() == tile_pos) {
							delete chunk.tiles[i];
							chunk.tiles.erase(chunk.tiles.begin() + i);
							chunk.grid_placed[TileChunk::size_c * tiles_i.y + tiles_i.x] = false;
						}
					}

					for (int i = 0; i < static_cast<int>(lines.size()); i++)
						if (lines[i].bottomLeft == tile_pos)
							lines.erase(lines.begin() + i);
				}
				else if (map->areas.empty() == false && sel_menu == Menu::Area) {
					for (int i = 0; i < static_cast<int>(map->areas.size()); i++) {
						int type = static_cast<int>(map->areas[i]->GetType());
						bool is_in_range = Object::AREA_MASK <= type && type < Object::ENEMY_MASK; // check if it is only area kinds

						if (is_in_range && isMousePressed == false) {
							delete map->areas.back();
							map->areas.erase(map->areas.end() - 1); // undo
							isMousePressed = true;
						}
					}
				}
				else if (map->bg_texures.empty() == false && sel_menu == Menu::Image) {
					for (int i = 0; i < static_cast<int>(map->bg_texures.size()); i++) {
						if (map->bg_texures[i]->GetInitPos() == tile_pos) {
							delete map->bg_texures[i];
							map->bg_texures.erase(map->bg_texures.begin() + i);
						}
					}
				}
			}
		}

		if (doodle::MouseIsPressed == false && isMousePressed == true)  // mouse released 
		{
			if (doodle::MouseButton == doodle::MouseButtons::Left) // was that left button
			{ 
				if (is_selecting_area) {
					temp_tile_datas.push_back(GetMousePos());

					TilePointer i = TileChunk::GetTile(s_type, temp_tile_datas);
					map->areas.push_back(i);
					temp_tile_datas.clear();

					Engine::getEffectSound().PlaySounds(8);
				}
			}
		}

		if (sel_menu == Menu::Mouse) isDragging = doodle::MouseIsPressed;

		isMousePressed = doodle::MouseIsPressed;
	}
	else
		check_editBar();

}

void MapEditor::update_fname_input()
{
	if (static_cast<int>(doodle::KeyboardButtons::_0) <= static_cast<int>(doodle::Key)
		and static_cast<int>(doodle::Key) <= static_cast<int>(doodle::KeyboardButtons::NumPad_9))
	{
		if (isKeyPressed == false and doodle::KeyIsPressed == true) {
			char c = static_cast<char>(std::tolower(to_string(doodle::Key).front()));
			save_dir_name += c;
		}
		isKeyPressed = doodle::KeyIsPressed;
	}

	if (save_dir_name.empty() == false and backspace.IsKeyPressed() == true)
		save_dir_name.pop_back();

	if (enter.IsKeyPressed())
	{
		isReadytoSave = false;
		save_map();
	}
}

void MapEditor::update_fselect_win()
{
	int index = 0;
	for (DOG::Button& f : file_buttons) {
		if (f.IsPressed() == true) {
			Engine::getEffectSound().PlaySounds(7);
			isSelectingFile = false;
			clear_map();
			map->SetMapDir(file_list[index]);
			index = 0;
			break;
		}
		index++;
	}
}

void MapEditor::load_fnames()
{
	file_list.clear();
	file_buttons.clear();

	std::string path = "Assets/maps/";

	for (auto& s : std::filesystem::directory_iterator(path)) {
		std::string dir_n = s.path().string().substr(path.size());
		if (dir_n != "empty_map.txt")
			file_list.push_back(dir_n);
	}

	for (int y = 0; y < file_list.size(); y++)
	{
		int isize = static_cast<int>(DOG::Button::size),
			isize_y = isize * y, isize_2 = isize / 2;
		int button_x = Engine::getWindow().GetSize().x / 5 - isize_2;
		int button_y = static_cast<int>(Engine::getWindow().GetSize().y * 0.7) - isize_y;
		file_buttons.push_back(DOG::Button{ math::ivec2{ button_x, button_y } });
	} // put buttons
}

#include <iostream>

void MapEditor::save_map()
{
	std::string dir_str = "Assets/maps/" + save_dir_name;
	const char* path_dir = dir_str.c_str();
	int result = _mkdir(path_dir);

	if (result == -1) {
		Engine::getLogger().LogError("Folder name \'" + save_dir_name + "\' alreay exist. Error Code : " + std::to_string(errno));
		return;
	}

	int xindex = 0, yindex = 0;
	for (TileChunk& m : map->whole_m)
	{
		std::ofstream file{ dir_str + '/' + std::to_string(yindex) + std::to_string(xindex) + ".txt" };
		file << yindex << ' ' << xindex << '\n' << std::endl;
		for (TilePointer t : m.tiles)
			file << t->Info() << std::endl;

		file.close();

		xindex++;
		if(xindex % GameMap::ChunckSize.x == 0)
		{
			xindex = 0;
			yindex++;
		}
	}

	std::ofstream bgimgfile{ dir_str + '/' + "bg_textures.txt" };
	for (TilePointer bg : map->bg_texures)
		bgimgfile << bg->Info() << std::endl;
	bgimgfile.close();

	std::ofstream areafile{ dir_str + '/' + "area_datas.txt" };
	for (TilePointer a : map->areas)
		areafile << a->Info() << std::endl;
	areafile.close();

	int chunk_size = static_cast<int>(map->whole_m.size());
	if (chunk_size < ChunkNumber)
		for (int& i = chunk_size; i < ChunkNumber; i++) {
			std::ofstream file{ dir_str + '/' + std::to_string(yindex) + std::to_string(xindex) + ".txt" };
			file << yindex << ' ' << xindex << '\n' << std::endl;

			file.close();
		}

	system("cls");
	std::cout << "Save Complete\n" << std::endl;
	std::cout << "Folder Name : " + save_dir_name << std::endl;
	std::cout << "Local Path : " + dir_str << std::endl;
}

void MapEditor::check_editBar()
{
	int index = 0;
	for (DOG::Button& b : menu_buttons)
	{
		if (b.IsPressed() == true)
		{
			Engine::getEffectSound().PlaySounds(7);
			s_type = Object::Type::None;

			isMenuOpened = false;
			isReadytoSave = false;
			isSelectingFile = false;

			switch (static_cast<Menu>(index))
			{
			case Menu::Mouse:
				sel_menu = static_cast<Menu>(index);
				break;
			case Menu::Load:
				isSelectingFile = !isSelectingFile;
				load_fnames();
				break;
			case Menu::Save:
				isReadytoSave = !isReadytoSave;
				save_dir_name.clear();
				break;
			case Menu::Clear:
				clear_map();
				break;
			default:
				isMenuOpened = true;
				sel_menu = static_cast<Menu>(index);
				Engine::getLogger().LogDebug(std::to_string(static_cast<int>(sel_menu)));
				break;
			}
		}
		index++;
	}

	if (isMenuOpened == true) {
		int index2 = 0;
		int selected_index = static_cast<int>(sel_menu) - 1; // Menu::Mouse
		for (DOG::Button& i : button_list[static_cast<int>(selected_index)]) {
			if (i.IsPressed() == true) {
				Engine::getEffectSound().PlaySounds(7);
				temp_tile_datas.clear();
				switch (sel_menu)
				{
				case Menu::Block:
					s_type = static_cast<Object::Type>(Object::BLOCK_MASK + index2); break;
				case Menu::Area:
					s_type = static_cast<Object::Type>(Object::AREA_MASK + index2); break;
				case Menu::Enemy:
					s_type = static_cast<Object::Type>(Object::ENEMY_MASK + index2); break;
				case Menu::Item:
					s_type = static_cast<Object::Type>(Object::ITEM_MASK + index2); break;
				case Menu::Image:
					s_type = Object::Type::Image;
					image_selected = index2;
					break;
				default: break;
				}
				Engine::getLogger().LogDebug(std::to_string(static_cast<int>(s_type)));
				isMenuOpened = false;
			}
			index2++;
		}
	}
}

void MapEditor::clear_map()
{
	for (TileChunk& d : map->whole_m)
		d.Unload();

	for (TilePointer a : map->areas)
		delete a;

	for (TilePointer i : map->bg_texures)
		delete i;

	map->bg_texures.clear();
	map->areas.clear();
	lines.clear();
}

void MapEditor::place_plant(TileChunk& chunk, TilePointer t)
{
	Object::Plant* p = static_cast<Object::Plant*>(t);
	int y_gap = temp_tile_datas[1].y - temp_tile_datas[0].y;
	int y_gap_index = y_gap / TilePixel;

	for (int i = 0; i <= (int)(y_gap_index / 2); i++) {
		int x = temp_tile_datas.front().x;
		i % 2 == 0 ? x -= TilePixel : x += TilePixel;
		TilePointer leaf = new Object::Plant::Leaf{ p, { x, temp_tile_datas.front().y + (i * 2) * TilePixel} };
		leaf->SetSprite(&block_image);
		chunk.tiles.push_back(leaf);
	}

	for (int i = 0; i <= y_gap_index; i++) {
		TilePointer stem = new Object::Plant::Stem{ p,{ temp_tile_datas.front().x, temp_tile_datas.front().y + i * TilePixel } };
		stem->SetSprite(&block_image);
		chunk.tiles.push_back(stem);
	}

}

void MapEditor::DrawDynamic()
{
	doodle::push_settings();
	doodle::apply_translate(-camera->GetPosition().x, -camera->GetPosition().y);
	doodle::apply_scale(scale_amt, scale_amt);

	if (isEditing == true) {

		math::ivec2 mouseToChunk = GetMousePos() / ChunkPixel * ChunkPixel;
		//	math::ivec2 chunkSizePos = mouseToChunk + math::ivec2{

		int lenx = mouseToChunk.y + ChunkPixel,
			leny = mouseToChunk.x + ChunkPixel;

		int t_ = static_cast<int>(s_type);
		bool isinrange = Object::AREA_MASK <= t_ && t_ < Object::ENEMY_MASK;

		if (isMousePressed == true && isinrange == true && temp_tile_datas.empty() == false) {
			math::ivec2 pos = { temp_tile_datas.front().x, temp_tile_datas.front().y };
			math::ivec2 dir;
			int x1 = static_cast<int>(GetMousePos().x), y1 = static_cast<int>(GetMousePos().y);
			if (pos.x < x1) dir.x = 1;
			if (pos.x > x1) dir.x = -1;
			if (pos.y < y1) dir.y = 1;
			if (pos.y > y1) dir.y = -1;

			int sqlenx = std::abs(pos.x - x1) * dir.x, sqleny = std::abs(pos.y - y1) * dir.y;
			doodle::push_settings();
			doodle::set_fill_color(200, 200);
			doodle::draw_rectangle(temp_tile_datas[0].x, temp_tile_datas[0].y, sqlenx, sqleny);
			doodle::pop_settings();
		}

		doodle::push_settings();
		doodle::set_outline_color(255);
		for (int i = 0; i <= TileChunk::size_c; i++) {
			int xoff = mouseToChunk.x + i * TilePixel, yoff = mouseToChunk.y + i * TilePixel;
			doodle::draw_line(xoff, mouseToChunk.y, xoff, lenx);
			doodle::draw_line(mouseToChunk.x, yoff, leny, yoff);
		}
		doodle::pop_settings();
		//Engine::getLogger().LogDebug(std::to_string(a2) + '\t' + std::to_string(b2));

		doodle::push_settings();
		for (int x = 0; x <= GameMap::map_width_i; x++)
			for (int y = 0; y <= GameMap::map_height_i; y++) {
				int xfr = x * ChunkPixel, yfr = y * ChunkPixel;
				int h = ChunkPixel * GameMap::map_height_i, w = ChunkPixel * GameMap::map_width_i;
				doodle::set_outline_color(0, 255, 0);
				doodle::draw_line(xfr, 0, xfr, h);
				doodle::draw_line(0, yfr, w, yfr);

				int index = GameMap::map_width_i * y + x;
				doodle::set_outline_color(0);
				doodle::draw_text(std::to_string(index), xfr, yfr);
			}
		doodle::pop_settings();


		if (temp_tile_datas.empty() == false && TileChunk::GetTile(s_type)->par_num() == 2) {
			doodle::push_settings();
			doodle::set_fill_color(255, 100);
			doodle::draw_rectangle(temp_tile_datas[0].x, temp_tile_datas[0].y, Object::Base::size, Object::Base::size);
			doodle::pop_settings();
		}

		for (math::irect2 i : lines) {
			doodle::push_settings();
			doodle::set_fill_color(0, 255, 0, 50);
			doodle::draw_rectangle(i.bottomLeft.x, i.bottomLeft.y, Object::Base::size, Object::Base::size);
			doodle::draw_rectangle(i.topRight.x, i.topRight.y, Object::Base::size, Object::Base::size);
			doodle::set_outline_width(4);
			doodle::set_outline_color(255, 200);
			doodle::draw_line(i.bottomLeft.x + Object::Base::size / 2, i.bottomLeft.y + Object::Base::size / 2,
				i.topRight.x + Object::Base::size / 2, i.topRight.y + Object::Base::size / 2);
			doodle::set_outline_width(1);
			doodle::set_outline_color(0);
			doodle::set_fill_color(220);
			doodle::draw_text("R", i.bottomLeft.x, i.bottomLeft.y);
			doodle::pop_settings();
		}

	}

	//doodle::draw_ellipse(cursorPos.x + cam.Get_iPosition().x, cursorPos.y + cam.Get_iPosition().y, 15);
	doodle::pop_settings();

}

void MapEditor::DrawStatic()
{
	if (isEditing == true)
	{
		int b2 = static_cast<int>(DOG::Button::size) * 2;
		int winy = Engine::getWindow().GetSize().y - b2;

		doodle::push_settings(); // white space
		doodle::set_fill_color(255, 100);
		doodle::draw_rectangle(0, winy, Engine::getWindow().GetSize().x, b2);
		doodle::pop_settings();

		for (DOG::Button& b : menu_buttons) {
			b.Draw();
		}

		int selected_index = static_cast<int>(sel_menu) - 1;
		if (isMenuOpened == true && sel_menu != Menu::Mouse)
			for (DOG::Button& k : button_list[static_cast<int>(selected_index)]) {
				k.Draw();
			}

		if (isSelectingFile == true)
		{
			int index = 0;
			for (DOG::Button& f : file_buttons)
			{
				f.Draw();
				doodle::draw_text(file_list[index], f.GetPosition().x, f.GetPosition().y);
				index++;
			}
		}

		if (isReadytoSave == true)
		{
			doodle::push_settings();
			doodle::set_fill_color(255, 100);
			doodle::draw_rectangle(Engine::getWindow().GetSize().x / 4, Engine::getWindow().GetSize().y / 2, 600, 100);
			doodle::set_fill_color(255);
			doodle::draw_text(save_dir_name, Engine::getWindow().GetSize().x / 4, Engine::getWindow().GetSize().y / 2);
			doodle::pop_settings();
		}

		if (isDragging == true)
		{
			int cursor_size = 32;
			math::ivec2 mouse_off = Engine::getInput().GetMousePosition() - cursor_size / 2;

			doodle::push_settings();
			doodle::set_fill_color(255, 200);
			doodle::draw_rectangle(mouse_off.x, mouse_off.y, cursor_size, cursor_size);
			doodle::pop_settings();
		}

	}
	if (s_type == Object::Type::Normal)
	{
		if (currentChapter == 2)
		{
			doodle::draw_image(*block_image.GetImg(24+Normal_num), Engine::getInput().GetMousePosition().x, Engine::getInput().GetMousePosition().y);
		}
		else {
			doodle::draw_image(*block_image.GetImg(Normal_num), Engine::getInput().GetMousePosition().x , Engine::getInput().GetMousePosition().y);
		}
		
	}
}

bool MapEditor::IsConfigurating()
{
	return isEditing || isSelectingFile || isReadytoSave;
}