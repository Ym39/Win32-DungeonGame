#include "CUI.h"
#include"CStatusManger.h"

CUI::CUI():curSelectIdx_yesorno(0),curSelectIdx_4answer(0),nextIndexTemp(NULL)
{
	Dialog_Bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_UIBOX));
	EndScene = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_ENDSCENE));
	DieScene = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_DIDESCENE));
}

void CUI::UIDraw(HDC BackBuffer)
{
	UIstate tempUistate = CStatusManger::Getinstance()->GetUiState();
	SceneState sceneState = CStatusManger::Getinstance()->GetSceneState();
	char* text;
	char* YesText;
	char* NoText;

	if (tempUistate == none)
	{
		return;
	}

	HDC MemDC;
	HBITMAP OldBit;
	MemDC = CreateCompatibleDC(BackBuffer);
	OldBit = (HBITMAP)SelectObject(MemDC, Dialog_Bit);

	TransparentBlt(BackBuffer, 0, 500, 650, 150, MemDC, 0, 0, 650, 150, RGB(255, 255, 255));

	SelectObject(MemDC, OldBit);
	DeleteDC(MemDC);
	
	if (sceneState == Move)
	{
		switch (tempUistate) //대화 상자위에 써지는 텍스트 컨트롤
		{
		case none:
			break;
		case PotalUi:
			text = "이동하시겠습니까?";
			YesText = "예";
			NoText = "아니오";
			TextOut(BackBuffer, 50, 520, text, strlen(text));
			TextOut(BackBuffer, 450, 520, YesText, strlen(YesText));
			TextOut(BackBuffer, 450, 560, NoText, strlen(NoText));
			break;
		case MonsterCollisionUi:
			text = "전투를 시작합니까?";
			YesText = "예";
			NoText = "아니오";
			TextOut(BackBuffer, 50, 520, text, strlen(text));
			TextOut(BackBuffer, 450, 520, YesText, strlen(YesText));
			TextOut(BackBuffer, 450, 560, NoText, strlen(NoText));
			break;
		}

		switch (tempUistate) //선택 커서 컨트롤
		{
		case none:
			break;
		case PotalUi:
			switch (curSelectIdx_yesorno)
			{
			case 0:
				Rectangle(BackBuffer, 435, 520, 445, 530);
				break;
			case 1:
				Rectangle(BackBuffer, 435, 560, 445, 570);
				break;
			}
			break;
		case MonsterCollisionUi:
			switch (curSelectIdx_yesorno)
			{
			case 0:
				Rectangle(BackBuffer, 435, 520, 445, 530);
				break;
			case 1:
				Rectangle(BackBuffer, 435, 560, 445, 570);
				break;
			}
			break;
		}
	}
	else if (sceneState == Battle)
	{

	}
	
}

void CUI::EndSceneDraw(HDC BackBuffer)
{
	HDC MemDC;
	HBITMAP OldBit;
	MemDC = CreateCompatibleDC(BackBuffer);
	OldBit = (HBITMAP)SelectObject(MemDC, EndScene);

	BitBlt(BackBuffer, 0, 0, 650, 650, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBit);
	DeleteDC(MemDC);
}

void CUI::DieSceneDraw(HDC BackBuffer)
{
	HDC MemDC;
	HBITMAP OldBit;
	MemDC = CreateCompatibleDC(BackBuffer);
	OldBit = (HBITMAP)SelectObject(MemDC, DieScene);

	BitBlt(BackBuffer, 0, 0, 650, 650, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBit);
	DeleteDC(MemDC);
}

void CUI::SetNextIndexInfo(int idx)
{
	nextIndexTemp = idx;
}

const int CUI::GetNextIndexInfo() const
{
	return nextIndexTemp;
}

void CUI::SetBattleScene(int idx)
{
	nextBattleSceneIdxTemp = idx;
}

const int CUI::GetBattleSceneIdx() const
{
	return nextBattleSceneIdxTemp;
}

void CUI::SetTempMonsterTile(CMapTile* temp)
{
	TempMonsterTile = temp;
}

void CUI::SetDead_MonsterTile()
{
	TempMonsterTile->SetDead();
}

void CUI::SetNextSpawnPos(int x, int y)
{
	nextSpawnXpos = x;
	nextSpawnYpos = y;
}

void CUI::SelectChange_YesOrNo()
{
	if (curSelectIdx_yesorno == 0)
	{
		curSelectIdx_yesorno = 1; return;
	}
	else if (curSelectIdx_yesorno == 1)
	{
		curSelectIdx_yesorno = 0; return;
	}
}



void CUI::SelectChoice(CStageInfo& stage, CBattleScene& battleScene,CPlayer* player,CMap& map, CScene& scene)
{
	UIstate tempUistate = CStatusManger::Getinstance()->GetUiState();

	switch (tempUistate)
	{
	case none:
		break;
	case PotalUi:
		if (curSelectIdx_yesorno == 0)
		{
			stage.SetCurMap(nextIndexTemp);
			CStatusManger::Getinstance()->SetInput_Move();
			CStatusManger::Getinstance()->reset_Ui();
			player->SetPlayerSpawn(map.GetSpawnPointLeft(), map.GetSpawnPointTop());
		}
		else if(curSelectIdx_yesorno == 1)
		{
			CStatusManger::Getinstance()->SetInput_Move();
			CStatusManger::Getinstance()->reset_Ui();
		}
		break;
	case MonsterCollisionUi:
		if (curSelectIdx_yesorno == 0)
		{
			stage.SetCurScene(nextBattleSceneIdxTemp);
			battleScene.InitBattleScene(scene, player);
			SetDead_MonsterTile();
			CStatusManger::Getinstance()->reset_Ui();
			CStatusManger::Getinstance()->SetScene_Battle();
			CStatusManger::Getinstance()->SetInput_Select();

		}
		else if (curSelectIdx_yesorno == 1)
		{
			CStatusManger::Getinstance()->SetInput_Move();
			CStatusManger::Getinstance()->reset_Ui();
		}
		break;
	}
}
