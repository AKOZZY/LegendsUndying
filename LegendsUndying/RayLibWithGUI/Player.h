#pragma once

#include "Entity.h"
#include "Weapon.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Attack(Weapon &weapon);
private:

};

