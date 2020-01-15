#include "CScene.h"

CScene::CScene():BackGroundIndex(-1),MonsterCount(0),isBoss(false)
{
	
}

CScene::~CScene()
{
	delete MonsterType;
}

const int CScene::GetBackGroundIndex() const
{
	return BackGroundIndex;
}

const int CScene::GetMonsterCount() const
{
	return MonsterCount;
}

const int CScene::GetMonsterType(int idx) const
{
	return MonsterType[idx];
}

const bool CScene::GetIsboss() const
{
	return isBoss;
}

const RECT& CScene::GetMonsterRect(int idx) const
{
	return MonsterRect[idx];
}

void CScene::LoadBattelSceneFile(char* strFileName)
{
	FILE* fp;
	fp = fopen(strFileName, "rt");
	int b_boss;

	fscanf(fp, "%d\n", &SceneINDEX);
	fscanf(fp, "%d\n", &BackGroundIndex);
	fscanf(fp, "%d\n", &MonsterCount);
	fscanf(fp, "%d\n", &b_boss);
	b_boss == 1 ? isBoss = true : isBoss = false;
	MonsterType = new int[MonsterCount];
	MonsterRect = new RECT[MonsterCount];

	for (int i = 0; i < MonsterCount; i++)
	{
		int typetemp, left, top, right, bottom;
		fscanf(fp, "%d %d %d %d %d\n", &typetemp, &left, &top, &right, &bottom);
		MonsterType[i] = typetemp;
		MonsterRect[i].left = left;
		MonsterRect[i].top = top;
		MonsterRect[i].right = right;
		MonsterRect[i].bottom = bottom;

	}

	fclose(fp);
}
