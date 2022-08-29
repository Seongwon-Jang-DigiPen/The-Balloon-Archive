/* my work
File Name: SaveManager.h
Project Name: The balloon
Author(s)
Main: Seongwon Jang
Sub: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#pragma once
#include "Vec2.h"
#include "../../Game/Headers/Prince.h"
#include "GameState.h"
class GameMap;

class SaveManager
{
public:
	class Data
	{
		friend class SaveManager;

		DOG::GameState::Chapter d_chapter = DOG::GameState::Chapter::CHAPTER1;
		math::vec2 d_balloonPosition = { 640,480 };
		Prince::BALLOONSTATE d_balloonState = Prince::BALLOONSTATE::Normal;
		int d_helium = 0;
		bool d_redblue = false;
	public:
		DOG::GameState::Chapter GetChapter() const { return d_chapter; }
		math::vec2 GetPosition() const { return d_balloonPosition; }
		Prince::BALLOONSTATE Getstate() const { return d_balloonState; }
		int GetHelium() const { return d_helium; }
		bool GetRedBlue() const { return d_redblue; }
		std::string GetChapterString()
		{
			switch (this->d_chapter)
			{
			case DOG::GameState::Chapter::CHAPTER1:
				return "Chapter1";
				break;
			case DOG::GameState::Chapter::CHAPTER2:
				return "Chapter2";
				break;
			case DOG::GameState::Chapter::CHAPTERBOSS:
				return "ChapterBoss";
				break;
			default:
				break;
			}
		}
		std::wstring GetChapterwString()
		{
			switch (this->d_chapter)
			{
			case DOG::GameState::Chapter::CHAPTER1:
				return L"Chapter1";
				break;
			case DOG::GameState::Chapter::CHAPTER2:
				return L"Chapter2";
				break;
			case DOG::GameState::Chapter::CHAPTERBOSS:
				return L"ChapterBoss";
				break;
			default:
				break;
			}
		}
	};
private:
	std::wstring documentPath;
	std::wstring savetxtPath;
	std::wstring mapDirPath;
	const std::wstring directoryName = L"/The Balloon";
	const std::wstring savefileName = L"/save.txt";
	const std::wstring mapdirectoryName = L"/SaveMapData";
	//const std::string saveDir_name = "Assets/Save/save.txt";
	//const std::string mapDir_name = "Assets/maps/SaveMapData";
	const std::wstring copyFrom = L"Assets/Save";
	Data data;
	bool haveAData = true;
	bool loadGame = false;
public:
	SaveManager();
	
	void CopySaveFile();
	void Save(DOG::GameState::Chapter c, Prince& p, GameMap* G);
	
	void SetChapter1();
	void SetChapter2();

	void SaveData();
	void SaveMapData(GameMap* map);
	void LoadData();
	Data GetData() const { return data; }
	bool CheckHaveAData() const { return haveAData; }
	bool GetloadGame() const { return loadGame; }
	void SetLoadGame(bool set) { loadGame = set; }
	std::wstring Get_MapDirPath() const { return mapDirPath; }

};


