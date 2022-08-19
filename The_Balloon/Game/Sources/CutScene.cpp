/*
File Name: CutScene.cpp
Project Name: The balloon
Author(s)
Main: Sangbeom Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */

#include <doodle/doodle.hpp>
#include "../../Engine/Headers/Engine.h"
#include "../Headers/CutScene.h"
#include "../Headers/Screens.h"

CutScene::CutScene(int statenow)
	: nextImage(DOG::Input::Keyboard::Z),
	skip(DOG::Input::Keyboard::Esc),
	stateNow(statenow),
	currState(nullptr),
	time(0)
{}

void CutScene::ImageLoad() {
	switch (stateNow) {
	case 0:
		sprite.Load("assets/Cutscene/Maincut.spt");
		break;
	case 1:
		sprite.Load("assets/Cutscene/Castlecut.spt");
		break;
	case 2:
		sprite.Load("assets/Cutscene/Kingcut.spt");
		break;
	case 3:
		sprite.Load("assets/Cutscene/King2cut.spt");
		break;
	case 4:
		sprite.Load("assets/Cutscene/Exilecut.spt");
		break;
	case 5:
		sprite.Load("assets/Cutscene/Loadcut.spt");
		break;
	case 6:
		sprite.Load("assets/Cutscene/Ch1endcut.spt");
		break;
	case 7:
		sprite.Load("assets/Cutscene/Ch2startcut.spt");
		break;
	case 8:
		sprite.Load("assets/Cutscene/Loadcut2.spt");
		break;
	case 9:
		sprite.Load("assets/Cutscene/Endingcut.spt");
		break;
	}
}

void CutScene::Load() {
	currState = States[stateNow];
	currState->Enter(this);
}

void CutScene::Update(double dt) {
	currState->Update(this, dt);
	currState->TestForExit(this);
	sprite.Update(dt);
}

void CutScene::ChangeState(State* newState) {
	currState = newState;
	currState->Enter(this);
}

void CutScene::State_Start::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_Start::Update(CutScene*, double) {}

void CutScene::State_Start::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.IsAnimationDone() == true) {
		if (cutscene->nextImage.IsKeyPressed() == true) {
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::CutScene1));
		}
	}
	if (cutscene->skip.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene));
	}
}

void CutScene::State_Castle::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
	Engine::getEffectSound().PlaySounds(10);
}

void CutScene::State_Castle::Update(CutScene*, double) {}

void CutScene::State_Castle::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.IsAnimationDone() == true) {
		if (cutscene->nextImage.IsKeyPressed() == true) {
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::CutScene2));
		}
	}
	if (cutscene->skip.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene));
		Engine::getEffectSound().Unload();
	}
}

void CutScene::State_King::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_King::Update(CutScene*, double) {}

void CutScene::State_King::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.GetAnimationIndex() >= 36 && cutscene->nextImage.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::CutScene3));
	}
	if (cutscene->skip.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene));
	}
}

void CutScene::State_King2::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_King2::Update(CutScene*, double) {}

void CutScene::State_King2::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.GetAnimationIndex() >= 195 && cutscene->nextImage.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::CutScene4));
	}
	if (cutscene->skip.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene));
	}
}

void CutScene::State_Exile::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_Exile::Update(CutScene*, double) {}

void CutScene::State_Exile::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.IsAnimationDone() == true) {
		if (cutscene->nextImage.IsKeyPressed() == true) {
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene));
		}
	}
	if (cutscene->skip.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene));
	}
}

void CutScene::State_Load::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_Load::Update(CutScene*, double) {}

void CutScene::State_Load::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.IsAnimationDone() == true) {
		Engine::getSaveManager().SetChapter1();
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::Tutorial));
	}
}

void CutScene::State_1End::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_1End::Update(CutScene*, double) {}

void CutScene::State_1End::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.IsAnimationDone() == true) {
		if (cutscene->nextImage.IsKeyPressed() == true) {
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::CutScene6));
		}
	}
	if (cutscene->skip.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene2));
	}
}

void CutScene::State_2Start::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_2Start::Update(CutScene*, double) {}

void CutScene::State_2Start::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.IsAnimationDone() == true) {
		if (cutscene->nextImage.IsKeyPressed() == true) {
			Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene2));
		}
	}
	if (cutscene->skip.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::LoadScene2));
	}
}

void CutScene::State_Load2::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_Load2::Update(CutScene*, double) {}

void CutScene::State_Load2::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.IsAnimationDone() == true) {
		Engine::getSaveManager().SetChapter2();
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::Chapter2));
	}
}

void CutScene::State_End::Enter(CutScene* cutscene) {
	cutscene->sprite.PlayAnimation(0);
}

void CutScene::State_End::Update(CutScene*, double) {}

void CutScene::State_End::TestForExit(CutScene* cutscene) {
	if (cutscene->sprite.IsAnimationDone() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::Main));
	}
	if (cutscene->skip.IsKeyPressed() == true) {
		Engine::getGSManager().SetNextState(static_cast<int>(Screens::Main));
	}
}

void CutScene::Draw() {
	doodle::push_settings();
	doodle::set_image_mode(doodle::RectMode::Center);
	sprite.Draw({ static_cast<double>(Engine::getWindow().GetSize().x / 2),
		static_cast<double>(Engine::getWindow().GetSize().y / 2) }, false);
	doodle::pop_settings();
}

void CutScene::Unload() {
	currState = nullptr;
}