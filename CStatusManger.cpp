#include "CStatusManger.h"

InputState CStatusManger::GetInputState() const
{
	return inputState;
}

UIstate CStatusManger::GetUiState() const
{
	return uiState;
}

SceneState CStatusManger::GetSceneState() const
{
	return sceneState;
}

void CStatusManger::SetInput_Move()
{
	inputState = Move;
}

void CStatusManger::SetInput_Select()
{
	inputState = Select;
}

void CStatusManger::SetScene_Dungeon()
{
	sceneState = Dungeon;
}

void CStatusManger::SetScene_Battle()
{
	sceneState = Battle;
}

void CStatusManger::SetScene_GameEnd()
{
	sceneState = GameEnd;
}

void CStatusManger::SetScene_Died()
{
	sceneState = Died;

}

void CStatusManger::reset_Ui()
{
	uiState = none;
}

void CStatusManger::SetUi_PotalUi()
{
	uiState = PotalUi;
}

void CStatusManger::SetUi_MonsterCollisionUi()
{
	uiState = MonsterCollisionUi;
}



CStatusManger* CStatusManger::instance = nullptr;
