#include "CMapTile.h"
CMapTile::CMapTile() :TileType(0), isCollider(false), isGate(false), isShop(false), isMonster(false), MonsterType(0), SceneIndex(-1), nextIndex(-1), isSpawn(false),isDead(false)
{
	tileRect.left = 0;
	tileRect.top = 0;
	tileRect.right = 0;
	tileRect.bottom = 0;
}

const int CMapTile::GetTileType() const
{
	return TileType;
}

void CMapTile::SetTileType(int type)
{
	if (type < 0 && type>2) return;
	TileType = type;
}

void CMapTile::SetCollider()
{
	isCollider = true;
}

void CMapTile::DeleteCollider()
{
	isCollider = false;
}

int CMapTile::GetLeft() const
{
	return tileRect.left;
}

void CMapTile::SetLeft(int left)
{
	tileRect.left = left;
}

int CMapTile::GetTop() const
{
	return tileRect.top;
}

void CMapTile::SetTop(int top)
{
	tileRect.top = top;
}

int CMapTile::GetRight() const
{
	return tileRect.right;
}

void CMapTile::SetRight(int right)
{
	tileRect.right = right;
}

int CMapTile::GetBottom() const
{
	return tileRect.bottom;
}

void CMapTile::SetBottom(int bottom)
{
	tileRect.bottom = bottom;
}

const RECT& CMapTile::GetTileRect() const
{
	return tileRect;
}

bool CMapTile::GetIsCollider() const
{
	return isCollider;
}

void CMapTile::SetGate()
{
	isGate = true;
}

void CMapTile::CancelGate()
{
	isGate = false;
}

bool CMapTile::GetIsGate() const
{
	return isGate;
}

void CMapTile::SetNextIndex(int idx)
{
	nextIndex = idx;
}

int CMapTile::GetNextIndex() const
{
	return nextIndex;
}

void CMapTile::SetShop()
{
	isShop = true;

}

void CMapTile::CancelShop()
{
	isShop = false;
}

bool CMapTile::GetIsShop() const
{
	return isShop;
}

void CMapTile::SetMonster(int type, int index)
{
	isMonster = true;
	MonsterType = type;
	SceneIndex = index;
}

void CMapTile::CancelMonster()
{
	isMonster = false;
	MonsterType = 0;
	SceneIndex = -1;
}

bool CMapTile::GetIsMonster() const
{
	return isMonster;
}

const int CMapTile::GetMonsterType() const
{
	return MonsterType;
}

int CMapTile::GetNextScene() const
{
	return SceneIndex;
}

bool CMapTile::GetIsDead() const
{
	return isDead;
}

void CMapTile::SetDead()
{
	isDead = true;
}

void CMapTile::SetSpawnPoint()
{
	isSpawn = true;
}

void CMapTile::CancleSpawnPoint()
{
	isSpawn = false;
}

bool CMapTile::GetSpawnPoint() const
{
	return isSpawn;
}