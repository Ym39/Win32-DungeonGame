#pragma once
#include"framework.h"

class CScene
{
	int SceneINDEX;
	int BackGroundIndex;
	unsigned int MonsterCount;
	int* MonsterType;
	bool isBoss;

	RECT* MonsterRect;
public:
	CScene();
	~CScene();
	
	const int GetBackGroundIndex() const;
	const int GetMonsterCount() const;
	const int GetMonsterType(int idx) const;
	const bool GetIsboss() const;
	const RECT& GetMonsterRect(int idx) const;

	void LoadBattelSceneFile(char* strFileName);

};

