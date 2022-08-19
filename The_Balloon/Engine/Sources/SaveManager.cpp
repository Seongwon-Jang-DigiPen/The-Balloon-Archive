/*
File Name: SaveManager.cpp
Project Name: The balloon
Author(s)
Main: Seongwon Jang
Sub: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include "../Headers/SaveManager.h"

#include <direct.h>
#include <iostream>
#include "../Headers/Engine.h"
#include <fstream>
#include <string>

#include "../../Game/Headers/MapEditor.h"
#include <filesystem>
#include <ShlObj_core.h>

void SaveManager::Save(DOG::GameState::Chapter c, Prince& p, GameMap* map)
{
	data.d_chapter = c;
	data.d_balloonPosition = p.GetStartPos();
	data.d_balloonState = p.GetBalloonState();
	data.d_helium = (int)p.GetHelium();
	data.d_redblue = map->RedBlue;
	SaveMapData(map);
	SaveData();
}


void SaveManager::SetChapter1()
{
	data.d_helium = 0;
	data.d_chapter = DOG::GameState::Chapter::CHAPTER1;
	data.d_balloonState = Prince::BALLOONSTATE::Normal;
	data.d_balloonPosition = { 640,360 };
	data.d_redblue = false;
}


void SaveManager::SetChapter2()
{
	data.d_helium = 0;
	data.d_chapter = DOG::GameState::Chapter::CHAPTER2;
	data.d_balloonState = Prince::BALLOONSTATE::Normal;
	data.d_balloonPosition = { 640,360 };
	data.d_redblue = false;
}


void SaveManager::CopySaveFile() // when we start game, we will create new save file
{
	std::filesystem::remove_all(documentPath + directoryName); // delete Map folder
	std::filesystem::create_directory(documentPath + directoryName);
	std::filesystem::copy("Assets/Save", documentPath + directoryName, std::filesystem::copy_options::recursive); // copy map folder
	SetChapter1();
	SaveData();
}


SaveManager::SaveManager()
{
	PWSTR path = NULL;
	SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &path); //document path.
	documentPath = path;
	CoTaskMemFree(path);

	bool exist = std::filesystem::exists(documentPath + directoryName);

	if (exist == false)
	{
		std::filesystem::create_directory(documentPath + directoryName);
		std::filesystem::copy(copyFrom, documentPath + directoryName, std::filesystem::copy_options::recursive); // copy map folder
	}

	savetxtPath = documentPath + directoryName + savefileName;
	mapDirPath = documentPath + directoryName + mapdirectoryName;
}

void SaveManager::SaveData()
{
	const std::filesystem::path& fileName = savetxtPath;
	if (exists(fileName))
	{

		Engine::getLogger().LogEvent("Find the SaveFile");
		if (fileName.extension() != ".txt") {

			throw std::runtime_error("Bad Filetype.  " + fileName.generic_string() + " not a sprite info file (.txt)");
		}
		std::ofstream file{ savetxtPath,std::ofstream::out | std::ofstream::trunc };
		if (file.is_open() == false) {
			throw std::runtime_error("Failed to load " + fileName.generic_string());
		}
		file << "Chapter" << ' ' << static_cast<int>(data.d_chapter) << std::endl;
		file << "Position" << ' ' << data.d_balloonPosition.x << ' ' << data.d_balloonPosition.y << std::endl;
		file << "BallonState" << ' ' << static_cast<int>(data.d_balloonState) << std::endl;
		file << "Helium" << ' ' << static_cast<int>(data.d_helium) << std::endl;
		file << "REDBLUE" << ' ' << data.d_redblue << std::endl;
		file.close();
	}
	else
	{
		Engine::getLogger().LogEvent("SaveFile did not exist");
	}
}

void SaveManager::LoadData()
{
	Engine::getLogger().LogEvent("Check the SaveFile");
	const std::filesystem::path& fileName = savetxtPath;
	if (exists(fileName))
	{

		Engine::getLogger().LogEvent("Find the SaveFile");
		if (fileName.extension() != ".txt") {

			haveAData = false;
			throw std::runtime_error("Bad Filetype.  " + fileName.generic_string() + " not a sprite info file (.txt)");
		}
		std::ifstream inFile(fileName);
		if (inFile.is_open() == false) {
			haveAData = false;
			throw std::runtime_error("Failed to load " + fileName.generic_string());
		}

		std::string label;
		while (inFile.eof() == false) {
			inFile >> label;
			if (label == "Chapter") {
				int chapter;
				inFile >> chapter;
				data.d_chapter = static_cast<DOG::GameState::Chapter>(chapter);
			}
			else if (label == "Position") {
				double x, y;
				inFile >> x;
				inFile >> y;
				data.d_balloonPosition = { x,y };
			}
			else if (label == "BallonState") {
				int state;
				inFile >> state;
				data.d_balloonState = static_cast<Prince::BALLOONSTATE>(state);
			}
			else if (label == "Helium") {
				int Helium;
				inFile >> Helium;
				data.d_helium = Helium;
			}
			else if(label == "REDBLUE")
			{
				int redblue;
				inFile >> redblue;
				data.d_redblue = redblue;
			}
			else {
				Engine::getLogger().LogError("Unknown command " + label + " in anm file " + fileName.generic_string());
			}
		}
	}
	else
	{
		Engine::getLogger().LogEvent("SaveFile did not exist");
		haveAData = false;
	}
}


void SaveManager::SaveMapData(GameMap* map)
{
	using Tile = Object::Base;
	using TilePointer = Object::Base*;
	using TileChunk = GameMap::MapChunk;

	std::wstring dir_str = mapDirPath + L'/' + data.GetChapterwString();

	int xindex = 0, yindex = 0;
	for (TileChunk& m : map->whole_m)
	{
		std::ofstream file{ dir_str + L'/' + std::to_wstring(yindex) + std::to_wstring(xindex) + L".txt" };
		file << yindex << ' ' << xindex << '\n' << std::endl;
		for (TilePointer t : m.tiles)
			file << t->Info() << std::endl;

		file.close();

		xindex++;
		if (xindex % GameMap::ChunckSize.x == 0)
		{
			xindex = 0;
			yindex++;
		}
	}

	std::ofstream bgimgfile{ dir_str + L'/' + L"bg_textures.txt" };
	for (TilePointer bg : map->bg_texures)
		bgimgfile << bg->Info() << std::endl;
	bgimgfile.close();

	std::ofstream areafile{ dir_str + L'/' + L"area_datas.txt" };
	for (TilePointer a : map->areas)
		areafile << a->Info() << std::endl;
	areafile.close();

	int chunk_size = static_cast<int>(map->whole_m.size());
	if (chunk_size < MapEditor::ChunkNumber)
		for (int& i = chunk_size; i < MapEditor::ChunkNumber; i++) {
			std::ofstream file{ dir_str + L'/' + std::to_wstring(yindex) + std::to_wstring(xindex) + L".txt" };
			file << yindex << L' ' << xindex << L'\n' << std::endl;

			file.close();
		}

	system("cls");
	std::cout << "Save Complete\n" << std::endl;
	std::cout << "Folder Name : " + data.GetChapterString() << std::endl;
}
