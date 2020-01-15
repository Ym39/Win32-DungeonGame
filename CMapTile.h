#pragma once
#include<Windows.h>

class CMapTile
{
	RECT tileRect;
	int TileType;
	bool isCollider;
	bool isGate;
	bool isShop;
	bool isMonster;
	bool isSpawn;
	int MonsterType;
	int SceneIndex; //Ÿ�Ͽ� ���Ͱ� ���� ��� �̾��� ���� �ε���
	int nextIndex;
	bool isDead;
public:
	CMapTile();

	const int GetTileType() const;
	void SetTileType(int type);
	void SetCollider();
	void DeleteCollider();
	bool GetIsCollider() const;

	void SetGate();
	void CancelGate();
	bool GetIsGate() const;
	void SetNextIndex(int idx); 
	int GetNextIndex() const; 

	void SetShop();
	void CancelShop();
	bool GetIsShop() const;
	
	void SetMonster(int type,int index);
	void CancelMonster();
	bool GetIsMonster() const;
	const int GetMonsterType() const;
	int GetNextScene() const;
	bool GetIsDead() const;
	void SetDead();

	void SetSpawnPoint();
	void CancleSpawnPoint();
	bool GetSpawnPoint() const;
	
	int GetLeft() const;
	void SetLeft(int left);
	int GetTop() const;
	void SetTop(int top);
	int GetRight() const;
	void SetRight(int right);
	int GetBottom() const;
	void SetBottom(int bottom);

	const RECT& GetTileRect() const;
};

