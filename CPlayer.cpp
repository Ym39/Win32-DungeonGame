#include "CPlayer.h"

CPlayer::CPlayer():xpos(0),ypos(0),speed(1),curState(FRONT),Hp(100),STR(30)
{
	bit_Player_Front = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_FRONT));
	bit_Player_Back = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_BACK));
	bit_Player_Left = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_LEFT));
	bit_Player_Right = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_PLAYER_RIGHT));

}

void CPlayer::SetPlayerSpawn(int x, int y)
{
	xpos = x; ypos = y;
	UpdatePlayerRect();

}

void CPlayer::DrawPlayer(HDC BackBuffer)
{
	HDC MemDC;
	HBITMAP OldBit;
	MemDC = CreateCompatibleDC(BackBuffer);

	OldBit = (HBITMAP)SelectObject(MemDC, bit_Player_Front);
	switch (curState)
	{
	case FRONT:
		OldBit = (HBITMAP)SelectObject(MemDC, bit_Player_Front);
		break;
	case BACK:
		OldBit = (HBITMAP)SelectObject(MemDC, bit_Player_Back);
		break;
	case LEFT:
		OldBit = (HBITMAP)SelectObject(MemDC, bit_Player_Left);
		break;
	case RIGHT:
		OldBit = (HBITMAP)SelectObject(MemDC, bit_Player_Right);
		break;
	}

	TransparentBlt(BackBuffer, xpos, ypos, 65, 65, MemDC, 0, 0, 65, 65, RGB(255, 255, 255));

	SelectObject(MemDC, OldBit);
	DeleteDC(MemDC);

}

const int CPlayer::GetHP() const
{
	return Hp;
}

void CPlayer::AddDamage(int damage)
{
	Hp -= damage;
}

const int CPlayer::GetDamage() const
{
	return STR;
}

const bool CPlayer::isDead() const
{
	if (Hp <= 0)
		return true;
	else
		return false;
}

void CPlayer::MoveLeft()
{
	xpos -= speed;
	curState = LEFT;
	UpdatePlayerRect();
}

void CPlayer::MoveUp()
{
	ypos -= speed;
	curState = BACK;
	UpdatePlayerRect();
}

void CPlayer::MoveRight()
{
	xpos += speed;
	curState = RIGHT;
	UpdatePlayerRect();

}

void CPlayer::MoveDown()
{
	ypos += speed;
	curState = FRONT;
	UpdatePlayerRect();

}

void CPlayer::BackMove()
{
	switch (curState)
	{
	case FRONT:
		ypos -= speed;
		break;
	case BACK:
		ypos += speed;
		break;
	case LEFT:
		xpos += speed;
		break;
	case RIGHT:
		xpos -= speed;
		break;
	}
	UpdatePlayerRect();
}



void CPlayer::UpdatePlayerRect()
{
	PlayerRect.left = xpos;
	PlayerRect.top = ypos;
	PlayerRect.right = xpos + 65;
	PlayerRect.bottom = ypos + 65;
}

const RECT& CPlayer::GetPlayerRect() const
{
	return PlayerRect;
}
