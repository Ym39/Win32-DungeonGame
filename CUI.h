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

	CMapTile* TempMonsterTile;//전투 실시한 몬스터 타일을 죽음처리하기 위한 임시 포인터

	int nextIndexTemp; //다음 맵의 인덱스를 임시적으로 저장
	int nextBattleSceneIdxTemp; //다음 배틀씬 인덱스를 임시적으로 저장
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
	void SelectChange_YesOrNo(); //2지선다 커서 변경
	void SelectChoice(CStageInfo& stage,CBattleScene& battleScene,CPlayer* player,CMap& map,CScene& scene);         //z키를 눌러 선택 //이 함수는 결정에 따라 화면도 전환할 수 있으므로 다른 클래스와 의존도가 높습니다.
};

