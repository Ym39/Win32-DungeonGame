#pragma once
#include"framework.h"
enum MOVESTATE
{
	FRONT,BACK,LEFT,RIGHT
};

class CPlayer
{
private:
	int xpos;
	int ypos;
	int Hp;
	int STR;

	RECT PlayerRect;
	MOVESTATE curState;

	int speed;

	HBITMAP bit_Player_Left;
	HBITMAP bit_Player_Front;
	HBITMAP bit_Player_Back;
	HBITMAP bit_Player_Right;
public:
	CPlayer();

	void SetPlayerSpawn(int x, int y);

	void DrawPlayer(HDC BackBuffer);

	const int GetHP() const;

	void AddDamage(int damage);
	const int GetDamage() const;
	const bool isDead() const;

	void MoveLeft();
	void MoveUp();
	void MoveRight();
	void MoveDown();
	void BackMove();
	void UpdatePlayerRect();

	const RECT& GetPlayerRect() const;
};

