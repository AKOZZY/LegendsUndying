#pragma once

#include "raylib.h"
#include "Collider.h"
#include <iostream>

enum WeaponType { MELEE, MAGIC, };

class Weapon
{
public:
	Weapon();
	void SetWeaponSprite(Texture2D sprite);
	Texture2D GetWeaponSprite();
	void SetProjectileSprite(Texture2D sprite);
	Texture2D GetProjectileSprite();
	void DrawWeapon(Vector2 position, Vector2 direction);
	void Attack(Vector2 position, Vector2 direction);
	float attackRate{};
	double weaponDamage{};
	bool hasAttacked{};
	Collider collider{};
	std::string weaponName{};
	WeaponType weaponType{};
private:
	Vector2 position{};
	Texture2D weaponSprite{};
	Texture2D projectileSprite{};
};

