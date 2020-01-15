#include "Enemy.h"

Enemy::Enemy():Hp(100),STR(15)
{
}

const bool Enemy::isDead() const
{
	if (Hp <= 0)
		return true;
	else
		return false;
}

const int Enemy::GetHP() const
{
	return Hp;
}

int Enemy::AddDamage(int damage)
{
	Hp -= damage;
	return Hp;
}

int Enemy::GetAttack() const
{
	return STR;
}
