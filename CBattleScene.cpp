#include "CBattleScene.h"

CBattleScene::CBattleScene():BackGroundIndex(NULL),MonsterCount(NULL),MonsterType(nullptr),isBoss(NULL),cursor(0),player(nullptr),enemy(nullptr),MonsterRect(nullptr),curAttack(SMITE),curPhase(playerTurn)
{
	BackGroundBit[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND1));
	BackGroundBit[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND2));
	BackGroundBit[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND3));

	MonsterBit[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_MONSTER1));
	MonsterBit[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_MONSTER2));
	MonsterBit[2] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_MONSTER3));
	MonsterBit[3] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_MONSTER4));

	BossBit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_BOSS));
	Dialog_Bit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_UIBOX));
}

CBattleScene::~CBattleScene()
{
	//delete MonsterType;
	//delete[] enemy;
	//delete[] MonsterRect;
}

void CBattleScene::InitBattleScene(const CScene& sceneinfo, CPlayer* player)
{
	BackGroundIndex = sceneinfo.GetBackGroundIndex();
	MonsterCount = sceneinfo.GetMonsterCount();
	MonsterType = new int[MonsterCount];
	MonsterRect = new RECT[MonsterCount];
	enemy = new Enemy[MonsterCount];
	
	for (int i = 0; i < MonsterCount; i++)
	{
		MonsterType[i] = sceneinfo.GetMonsterType(i);
		MonsterRect[i] = sceneinfo.GetMonsterRect(i);
	}

	isBoss = sceneinfo.GetIsboss();
	this->player = player;

	curPhase = playerTurn;
}


void CBattleScene::MoveCursor()
{
	switch (curPhase)
	{
	case playerTurn:
		if (cursor == 1)
			cursor = 0;
		else
			cursor++;
		break;
	case SelectMonster:
		if (cursor == MonsterCount - 1)
		{
			cursor = 0;
		}
		else
		{
			cursor++;
		}
		break;
	case ShowResult:
		break;
	case EnemyTurn:
		break;
	case End:
		break;
	}
}

void CBattleScene::ProgressButton()
{
	switch (curPhase)
	{
	case playerTurn:
		if (cursor == 0)
		{
			curAttack = SMITE;
		}
		else
		{
			curAttack = WINDMILL;
		}
		curPhase = SelectMonster;
		
		break;
	case SelectMonster:
		if (curAttack==SMITE)
		{
			if (enemy[cursor].isDead())
				break;
			else
			{
				enemy[cursor].AddDamage((player->GetDamage())*2);
			}
		}
		else
		{
			for (int i = 0; i < MonsterCount; i++)
			{
				enemy[i].AddDamage(player->GetDamage());
			}
		}
		curPhase = ShowResult;
		break;
	case ShowResult:
	    {
		int cheakMonster = 0;
		for (int i = 0; i < MonsterCount; i++)
		{
			if (enemy[i].isDead())
				cheakMonster++;
		}

		if (cheakMonster == MonsterCount)
			curPhase = End;
		else
			curPhase = EnemyTurn;
	    }
		break;
	case EnemyTurn:
		player->AddDamage(enemy[0].GetAttack());
		if (player->isDead())
		{
			curPhase = End;
		}
		else
		{
			curPhase = playerTurn;
		}
		break;
	case End:
		if (isBoss == true)
		{
			CStatusManger::Getinstance()->SetScene_GameEnd();
		}
		else if (player->isDead())
		{
			CStatusManger::Getinstance()->SetScene_Died();
		}
		else {
			CStatusManger::Getinstance()->SetScene_Dungeon();
			CStatusManger::Getinstance()->SetInput_Move();
		}
		break;
	}

}

void CBattleScene::DrawBattleScene(HDC BackBuffer)
{
	DrawBackGround(BackBuffer);
	DrawMonster(BackBuffer);
	DrawStateUi(BackBuffer);
	DrawMenuUi(BackBuffer);
	DrawCursor(BackBuffer);
}

void CBattleScene::DrawBackGround(HDC BackBuffer)
{
	HDC MemDC;
	HBITMAP OldBit;
	MemDC = CreateCompatibleDC(BackBuffer);
	OldBit = (HBITMAP)SelectObject(MemDC, BackGroundBit[BackGroundIndex]);

	BitBlt(BackBuffer, 0, 0, 650, 650, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBit);
	DeleteDC(MemDC);
}

void CBattleScene::DrawMonster(HDC BackBuffer)
{
	HDC MemDC;
	HBITMAP OldBit;
	MemDC = CreateCompatibleDC(BackBuffer);

	if (isBoss)
	{
		OldBit = (HBITMAP)SelectObject(MemDC, BossBit);
		TransparentBlt(BackBuffer, MonsterRect[0].left, MonsterRect[0].top,
			250, 250, MemDC, 0, 0, 250, 250, RGB(255, 255, 255));
		SelectObject(MemDC, OldBit);
		DeleteDC(MemDC);
		return;
	}

	for (int i = 0; i < MonsterCount; i++)
	{
		if (enemy[i].isDead())
			continue;
		int type = MonsterType[i];
		OldBit = (HBITMAP)SelectObject(MemDC, MonsterBit[type]);
		TransparentBlt(BackBuffer, MonsterRect[i].left, MonsterRect[i].top,
			100, 200, MemDC, 0, 0, 100, 200, RGB(48, 120, 128));
		SelectObject(MemDC, OldBit);
	}

	DeleteDC(MemDC);
}

void CBattleScene::DrawStateUi(HDC BackBuffer)
{
	HDC MemDC;
	HBITMAP OldBit;
	MemDC = CreateCompatibleDC(BackBuffer);
	OldBit = (HBITMAP)SelectObject(MemDC, Dialog_Bit);

	char playerHpState[20];
	

	TransparentBlt(BackBuffer, 0, 500, 650, 150, MemDC, 0, 0, 650, 150, RGB(255, 255, 255));//대화상자를 그립니다.

	//플레이어 hp 표시
	sprintf(playerHpState, "내 HP : %d", player->GetHP());
	TextOut(BackBuffer, 50, 520, playerHpState, strlen(playerHpState));

	//적 hp표시
	for (int i = 0; i < MonsterCount; i++)
	{
		if (enemy[i].isDead())
			continue;
		char enemyHpState[20];
		sprintf(enemyHpState, "HP : %d", enemy[i].GetHP());
		TextOut(BackBuffer, MonsterRect[i].left, MonsterRect[i].top, enemyHpState, strlen(enemyHpState));
	}
	

	SelectObject(MemDC, OldBit);
	DeleteDC(MemDC);
}

void CBattleScene::DrawMenuUi(HDC BackBuffer)
{
	switch (curPhase)
	{
	case playerTurn:
		TextOut(BackBuffer, 70, 540, "집중의 일격", strlen("집중의 일격"));
		TextOut(BackBuffer, 200, 540, "윈드밀", strlen("윈드밀"));
		break;
	case SelectMonster:
		TextOut(BackBuffer, 70, 540, "공격할 적을 선택해주세요.", strlen("공격할 적을 선택해주세요."));
		break;
	case ShowResult:
		if (curAttack == SMITE)
		{
			char t1[50];
			sprintf(t1, "적 하나에게 %d 데미지", (player->GetDamage())*2);
			TextOut(BackBuffer, 70, 540, t1, strlen(t1));
		}
		else
		{
			char t2[50];
			sprintf(t2, "적 전체에게 %d 데미지", player->GetDamage());
			TextOut(BackBuffer, 70, 540, t2, strlen(t2));
		}
		break;
	case EnemyTurn:
		char t3[50];
		sprintf(t3, "적의 공격!  %d 데미지를 입었다!", enemy[0].GetAttack());
		TextOut(BackBuffer, 70, 540, t3, strlen(t3));
		break;
	case End:
		if (player->isDead())
		{
			TextOut(BackBuffer, 70, 540, "사망하였습니다...", strlen("사망하였습니다..."));
		}
		else
		{
			TextOut(BackBuffer, 70, 540, "전투에서 승리하였습니다.", strlen("전투에서 승리하였습니다."));

		}
		break;
	}
}

void CBattleScene::DrawCursor(HDC BackBuffer)
{
	switch (curPhase)
	{
	case playerTurn:
		if (cursor == 0)
		{
			Rectangle(BackBuffer, 50, 540, 60, 550);
		}
		else
		{
			Rectangle(BackBuffer, 180, 540, 190, 550);
		}
		break;
	case SelectMonster:
		Rectangle(BackBuffer, MonsterRect[cursor].left+50, MonsterRect[cursor].top+20, MonsterRect[cursor].left +50 +20, MonsterRect[cursor].top +20+ 20);
		break;
	case ShowResult:
		break;
	case EnemyTurn:
		break;
	case End:
		break;
	}
}
