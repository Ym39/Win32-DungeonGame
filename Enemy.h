#pragma once
class Enemy
{
private:
	int Hp;  
	int STR;

public:
	Enemy();

	const bool isDead() const;
	const int GetHP() const;
	int AddDamage(int damage);
	int GetAttack() const;
};

