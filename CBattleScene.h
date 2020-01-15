#pragma once
#include"Enemy.h"
#include"CPlayer.h"
#include"framework.h"
#include"CScene.h"

enum BattlePhase
{
	playerTurn,SelectMonster,ShowResult,EnemyTurn,End
};

enum AttackType
{
	SMITE,WINDMILL
};

class CBattleScene
{
private:
	int BackGroundIndex;
	int MonsterCount;
	int* MonsterType;
	bool isBoss;

	CPlayer* player;
	Enemy* enemy;
	RECT* MonsterRect;

	int cursor;
	AttackType curAttack;
	BattlePhase curPhase;

	HBITMAP BackGroundBit[3];
	HBITMAP MonsterBit[4];
	HBITMAP BossBit;
	HBITMAP Dialog_Bit;
public:
	CBattleScene();
	~CBattleScene();

	void InitBattleScene(const CScene& sceneinfo, CPlayer* player);

	void MoveCursor();
	void ProgressButton();
	
	void DrawBattleScene(HDC BackBuffer);
	void DrawBackGround(HDC BackBuffer);
	void DrawMonster(HDC BackBuffer);
	void DrawStateUi(HDC BackBuffer);//hp«•Ω√
	void DrawMenuUi(HDC BackBuffer);
	void DrawCursor(HDC BackBuffer);

};

