#pragma once
#include"framework.h"

class CStageInfo
{
private:
	unsigned int MapCount;
	unsigned int BattleSceneCount;

	int CurMap;
	int CurScene;

	void LoadStageInfoFile();
public:
	CStageInfo();

	const unsigned int GetMapCount() const;
	const unsigned int GetBattleSceneCount() const;

	const int GetCurMap() const;
	void SetCurMap(int idx);
	const int GetCurScene() const;
	void SetCurScene(int idx);
};

