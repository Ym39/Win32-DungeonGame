#pragma once

enum InputState
{
	Move,Select
};

enum UIstate
{
	none,PotalUi,MonsterCollisionUi
};

enum SceneState
{
	Dungeon, Battle, GameEnd,Died
};

class CStatusManger
{
private:
	static CStatusManger* instance;

	InputState inputState;
	UIstate uiState;
	SceneState sceneState;

public:
	CStatusManger() :inputState(Move), uiState(none),sceneState(Dungeon) {}


	static CStatusManger* Getinstance()
	{
		if (instance == nullptr)
		{
			instance = new CStatusManger();
		}

		return instance;
	}

	InputState GetInputState() const;
	UIstate GetUiState() const;
	SceneState GetSceneState() const;

	void SetInput_Move();
	void SetInput_Select();

	void SetScene_Dungeon();
	void SetScene_Battle();
	void SetScene_GameEnd();
	void SetScene_Died();

	void reset_Ui();
	void SetUi_PotalUi();
	void SetUi_MonsterCollisionUi();
};

