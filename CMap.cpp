#include "CMap.h"

void CMap::DrawTile(HDC BackBuffer, int i, int j, int type)
{
	int x = Tile[i][j].GetLeft();
	int y = Tile[i][j].GetTop();

	HDC MemDC;
	HBITMAP OldBitmap;
	MemDC = CreateCompatibleDC(BackBuffer);
	switch (type)
	{
	case 1:
		OldBitmap = (HBITMAP)SelectObject(MemDC, TileBit[0]);
		break;
	case 2:
		OldBitmap = (HBITMAP)SelectObject(MemDC, TileBit[1]);
		break;
	default:
		DeleteDC(MemDC);
		return;
	}

	BitBlt(BackBuffer, x, y, 65, 65, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void CMap::DrawShop(HDC BackBuffer, int i, int j)
{
	int x = Tile[i][j].GetLeft();
	int y = Tile[i][j].GetTop();

	HDC MemDC;
	HBITMAP OldBitmap;
	MemDC = CreateCompatibleDC(BackBuffer);
	OldBitmap = (HBITMAP)SelectObject(MemDC, ShopBit);
	TransparentBlt(BackBuffer, x, y, 65, 65, MemDC, 0, 0, 65, 65, RGB(255, 255, 255));
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

void CMap::DrawMonster(HDC BackBuffer, int i, int j, int type)
{
	int x = Tile[i][j].GetLeft();
	int y = Tile[i][j].GetTop();

	HDC MemDC;
	HBITMAP OldBitmap;
	MemDC = CreateCompatibleDC(BackBuffer);
	switch (type)
	{
	case 1:
		OldBitmap = (HBITMAP)SelectObject(MemDC, MonsterBit[0]);
		break;
	case 2:
		OldBitmap = (HBITMAP)SelectObject(MemDC, MonsterBit[1]);
		break;
	default:
		DeleteDC(MemDC);
		return;
	}
	TransparentBlt(BackBuffer, x, y, 65, 65, MemDC, 0, 0, 65, 65, RGB(255, 255, 255));
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

CMap::CMap()
{
	Tile = new CMapTile * [10];
	for (int i = 0; i < 10; i++)
	{
		Tile[i] = new CMapTile[10];
	}

	int topTemp = 0;
	int bottomTemp = 65;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (j == 0)
			{
				Tile[i][j].SetLeft(0);
				Tile[i][j].SetTop(topTemp);
				Tile[i][j].SetRight(65);
				Tile[i][j].SetBottom(bottomTemp);
			}
			else
			{
				Tile[i][j].SetLeft(Tile[i][j - 1].GetLeft() + 65);
				Tile[i][j].SetTop(topTemp);
				Tile[i][j].SetRight(Tile[i][j - 1].GetRight() + 65);
				Tile[i][j].SetBottom(bottomTemp);
			}

		}
		topTemp += 65;
		bottomTemp += 65;
	}

	TileBit[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_WALL));
	TileBit[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_LOAD));
	ShopBit = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_SHOP));
	MonsterBit[0] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_MONSTER_EYE));
	MonsterBit[1] = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_MONSTER_DRAGON));

}

CMap::~CMap()
{
	for (int i = 0; i < 10; i++)
		delete[] Tile[i];
	delete[] Tile;
}

void CMap::DrawMap(HDC backBuffer)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			DrawTile(backBuffer, i, j, Tile[i][j].GetTileType());

		}
	}

	if (ShopCount != 0)
	{

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{

				if (Tile[i][j].GetIsShop() == true)
				{
					DrawShop(backBuffer, i, j);
				}

			}
		}
	}
	
	if (MonsterCount != 0)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{

				if (Tile[i][j].GetIsMonster() == true&&Tile[i][j].GetIsDead()==false)
				{
					DrawMonster(backBuffer, i, j, Tile[i][j].GetMonsterType());
				}

			}
		}
	}
}

bool CMap::CollisionCheack(const RECT playerRect) const
{
	RECT tempRect;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Tile[i][j].GetIsCollider())
			{
				if(IntersectRect(&tempRect, &Tile[i][j].GetTileRect(), &playerRect) == true)
				    return true;
			}
		}
	}
	return false;
}

bool CMap::PotalCollisionCheak(const RECT playerRect,int* nextIndex) const
{
	RECT tempRect;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Tile[i][j].GetIsGate())
			{
				if (IntersectRect(&tempRect, &Tile[i][j].GetTileRect(), &playerRect) == true)
				{
					*nextIndex = Tile[i][j].GetNextIndex();
					return true;
				}
			}
		}
	}
	return false;
}

bool CMap::EnemyCollisionCheak(const RECT playerRect,int* nextScene, CMapTile** temp) const
{
	RECT tempRect;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Tile[i][j].GetIsMonster()&&Tile[i][j].GetIsDead()==false)
			{
				if (IntersectRect(&tempRect, &Tile[i][j].GetTileRect(), &playerRect) == true)
				{
					*nextScene = Tile[i][j].GetNextScene();
					*temp = &(Tile[i][j]);
					return true;
				}
			}
		}
	}
	return false;
}




int CMap::GetSpawnPointLeft()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			if (Tile[i][j].GetSpawnPoint() == true)
			{
				return Tile[i][j].GetLeft();
			}

		}
	}
}

int CMap::GetSpawnPointTop()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{

			if (Tile[i][j].GetSpawnPoint() == true)
			{
				return Tile[i][j].GetTop();
			}

		}
	}
}

void CMap::LoadMapFile(char* strFileName)
{
	FILE* fp;
	fp = fopen(strFileName, "rt");
	int tempType;
	int isColl;
	int isGate;
	int index;
	int isShop;
	int isMonster;
	int MonsterType;
	int nextScene;
	int isSpawn;

	fscanf(fp, "%d\n", &CollisionCount);
	fscanf(fp, "%d\n", &GateCount);
	fscanf(fp, "%d\n", &ShopCount);
	fscanf(fp, "%d\n", &MonsterCount);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fscanf(fp, "%d %d %d %d %d %d %d %d %d\n", &tempType, &isColl, &isGate, &index, &isShop, &isMonster, &MonsterType, &nextScene, &isSpawn);
			Tile[i][j].SetTileType(tempType);
			if (isColl == 1) Tile[i][j].SetCollider();
			if (isGate == 1)Tile[i][j].SetGate();
			Tile[i][j].SetNextIndex(index);
			if (isShop == 1)Tile[i][j].SetShop();
			if (isMonster == 1)
			{
				Tile[i][j].SetMonster(MonsterType, nextScene);
			}
			if (isSpawn == 1)
			{
				Tile[i][j].SetSpawnPoint();
			}
		}
	}

	fclose(fp);
}


