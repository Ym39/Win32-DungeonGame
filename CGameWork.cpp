#include "CGameWork.h"
#include"framework.h"

CGameWork::CGameWork(void)
{
}

CGameWork::~CGameWork(void)
{
}

void CGameWork::SceneInit()
{
	BattleScene = new CBattleScene;
	Map = new CMap[Stage.GetMapCount()];
	Scene = new CScene[Stage.GetBattleSceneCount()];

	for (int i = 0; i < Stage.GetMapCount(); i++)
	{
		char number[20];
		char mapextension[10] = ".map";
		
		sprintf(number, "%d", i);
		strcat(number, mapextension);

		Map[i].LoadMapFile(number);
	}

	for (int i = 0; i < Stage.GetBattleSceneCount(); i++)
	{
		char scenenum[20];
		char sceneextension[10] = ".scene";
		sprintf(scenenum, "%d", i);
		strcat(scenenum, sceneextension);

		Scene[i].LoadBattelSceneFile(scenenum);
	}

	Player = new CPlayer;
	Player->SetPlayerSpawn(Map[0].GetSpawnPointLeft(), Map[0].GetSpawnPointTop());
	Ui = new CUI;
}

void CGameWork::SceneUpdate()
{
	int nextIndex;
	int nextScene;
	CMapTile* temp;
	if (CStatusManger::Getinstance()->GetInputState()==Move) 
	{
		if (Map[Stage.GetCurMap()].CollisionCheack(Player->GetPlayerRect()) == false
			&& Map[Stage.GetCurMap()].PotalCollisionCheak(Player->GetPlayerRect() , &nextIndex) == false)
		{
			if (keyState == Left)
			{
				Player->MoveLeft();
			}
			if (keyState == Up)
			{
				Player->MoveUp();
			}
			if (keyState == Right)
			{
				Player->MoveRight();

			}
			if (keyState == Down)
			{
				Player->MoveDown();
			}
		}
		else if (Map[Stage.GetCurMap()].CollisionCheack(Player->GetPlayerRect()) == true)
		{
			Player->BackMove();
		}
		else if (Map[Stage.GetCurMap()].PotalCollisionCheak(Player->GetPlayerRect(),&nextIndex) )
		{
			Player->BackMove();
			CStatusManger::Getinstance()->SetUi_PotalUi();
			CStatusManger::Getinstance()->SetInput_Select();
			Ui->SetNextIndexInfo(nextIndex);
		}
		if (Map[Stage.GetCurMap()].EnemyCollisionCheak(Player->GetPlayerRect(),&nextScene,&temp))
		{

			Player->BackMove();
			CStatusManger::Getinstance()->SetUi_MonsterCollisionUi();
			CStatusManger::Getinstance()->SetInput_Select();
			Ui->SetBattleScene(nextScene);
			Ui->SetTempMonsterTile(temp);

		}
	}
	else if (CStatusManger::Getinstance()->GetInputState() == Select)
	{
		if (CStatusManger::Getinstance()->GetSceneState() == Dungeon)
		{
			if (keyState == Up && keyCheack == false)
			{
				Ui->SelectChange_YesOrNo();
				keyCheack = true;

			}
			if (keyState == Down && keyCheack == false)
			{
				Ui->SelectChange_YesOrNo();
				keyCheack = true;

			}
			if (keyState == LEFT && keyCheack == false)
			{
				Ui->SelectChange_YesOrNo();
				keyCheack = true;

			}
			if (keyState == Right && keyCheack == false)
			{
				Ui->SelectChange_YesOrNo();
				keyCheack = true;

			}
			if (keyState == Z)
			{
					Ui->SelectChoice(Stage, *BattleScene, Player, Map[Ui->GetNextIndexInfo()], Scene[Ui->GetBattleSceneIdx()]);
					keyCheack = true;
			}
		}
		else if (CStatusManger::Getinstance()->GetSceneState() == Battle)
		{
			if (keyState == Up && keyCheack == false)
			{
				BattleScene->MoveCursor();
				keyCheack = true;

			}
			if (keyState == Down && keyCheack == false)
			{
				BattleScene->MoveCursor();
				keyCheack = true;

			}
			if (keyState == LEFT && keyCheack == false)
			{
				BattleScene->MoveCursor();
				keyCheack = true;

			}
			if (keyState == Right && keyCheack == false)
			{
				BattleScene->MoveCursor();
				keyCheack = true;

			}
			if (keyState == Z && keyCheack==false)
			{
				BattleScene->ProgressButton();
				keyCheack = true;
			}
		}
		else if (CStatusManger::Getinstance()->GetSceneState() == GameEnd)
		{
			if (keyState == Z && keyCheack == false)
			{
				SendMessage(exturn_hwnd, WM_DESTROY, NULL, NULL);
				keyCheack = true;
			}
		}
		else if (CStatusManger::Getinstance()->GetSceneState() == Died)
		{
			if (keyState == Z && keyCheack == false)
			{
				SendMessage(exturn_hwnd, WM_DESTROY, NULL, NULL);
				keyCheack = true;
			}
		}
	}
	
}

void CGameWork::SceneRender()
{
	if (CStatusManger::Getinstance()->GetSceneState() == Dungeon)
	{
		Map[Stage.GetCurMap()].DrawMap(m_hBackBuffer);
		Player->DrawPlayer(m_hBackBuffer);
		Ui->UIDraw(m_hBackBuffer);
	}
	else if (CStatusManger::Getinstance()->GetSceneState() == Battle)
	{
		BattleScene->DrawBattleScene(m_hBackBuffer);
	}
	else if (CStatusManger::Getinstance()->GetSceneState() == GameEnd)
	{
		Ui->EndSceneDraw(m_hBackBuffer);
	}
	else if (CStatusManger::Getinstance()->GetSceneState() == Died)
	{
		Ui->DieSceneDraw(m_hBackBuffer);
	}

	char string[100];
	SetBkColor(m_hBackBuffer, RGB(0, 0, 0));
	SetTextColor(m_hBackBuffer, RGB(255, 255, 255));
	sprintf(string, "FPS:%-4d", m_nFPS);
	TextOut(m_hBackBuffer, 0, 0, string, strlen(string));

}

void CGameWork::SceneRelease()
{
	delete Player;
	delete[] Map;
	delete[] Scene;
	delete Ui;
	delete BattleScene;
}