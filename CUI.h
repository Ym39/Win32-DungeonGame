#pragma once
#include"framework.h"
#include"CStageInfo.h"
#include"CPlayer.h"
#include"CMap.h"
#include"CBattleScene.h"
#include"CScene.h"
#include"CMapTile.h"

class CUI
{
private:
	unsigned int curSelectIdx_yesorno;
	unsigned int curSelectIdx_4answer;
	HBITMAP Dialog_Bit;
	HBITMAP EndScene;
	HBITMAP DieScene;

	CMapTile* TempMonsterTile;//���� �ǽ��� ���� Ÿ���� ����ó���ϱ� ���� �ӽ� ������

	int nextIndexTemp; //���� ���� �ε����� �ӽ������� ����
	int nextBattleSceneIdxTemp; //���� ��Ʋ�� �ε����� �ӽ������� ����
	int nextSpawnXpos;
	int nextSpawnYpos;

public:
	CUI();

	void UIDraw(HDC BackBuffer);
	void EndSceneDraw(HDC BackBuffer);
	void DieSceneDraw(HDC BackBuffer);

	void SetNextIndexInfo(int idx);
	const int GetNextIndexInfo() const;

	void SetBattleScene(int idx);
	const int GetBattleSceneIdx() const;

	void SetTempMonsterTile(CMapTile* temp);
	void SetDead_MonsterTile();

	void SetNextSpawnPos(int x, int y);
	void SelectChange_YesOrNo(); //2������ Ŀ�� ����
	void SelectChoice(CStageInfo& stage,CBattleScene& battleScene,CPlayer* player,CMap& map,CScene& scene);         //zŰ�� ���� ���� //�� �Լ��� ������ ���� ȭ�鵵 ��ȯ�� �� �����Ƿ� �ٸ� Ŭ������ �������� �����ϴ�.
};

