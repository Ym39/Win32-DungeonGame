#include "CStageInfo.h"

CStageInfo::CStageInfo():MapCount(0),BattleSceneCount(0),CurMap(0),CurScene(0)
{
	LoadStageInfoFile();
}

const unsigned int CStageInfo::GetMapCount() const
{
	return MapCount;
}

const unsigned int CStageInfo::GetBattleSceneCount() const
{
	return BattleSceneCount;
}

const int CStageInfo::GetCurMap() const
{
	return CurMap;
}

void CStageInfo::SetCurMap(int idx)
{
	CurMap = idx;
}

const int CStageInfo::GetCurScene() const
{
	return CurScene;
}

void CStageInfo::SetCurScene(int idx)
{
	CurScene = idx;
}

void CStageInfo::LoadStageInfoFile()
{
	FILE* fp;
	fp = fopen("stageinfo.stage", "rt");

	fscanf(fp, "%d\n", &MapCount);
	fscanf(fp, "%d\n", &BattleSceneCount);

	fclose(fp);
}
