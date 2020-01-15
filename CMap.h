#pragma once
#include"CMapTile.h"
#include"framework.h"

class CMap
{
private:
	CMapTile** Tile;

	int CollisionCount;
	int GateCount;
	int ShopCount;
	int MonsterCount;

	HBITMAP TileBit[2];
	HBITMAP ShopBit;
	HBITMAP MonsterBit[2];

	void DrawTile(HDC BackBuffer, int i, int j, int type);
	void DrawShop(HDC BackBuffer, int i, int j);
	void DrawMonster(HDC BackBuffer, int i, int j, int type);
public:
	CMap();
	~CMap();

	void DrawMap(HDC backBuffer);

	bool CollisionCheack(const RECT playerRect) const;
	bool PotalCollisionCheak(const RECT playerRect,int* nextIndex) const;
	bool EnemyCollisionCheak(const RECT playerRect,int* nextScene,CMapTile** temp) const;

	int GetSpawnPointLeft();
	int GetSpawnPointTop();

	void LoadMapFile(char* strFileName);
};

