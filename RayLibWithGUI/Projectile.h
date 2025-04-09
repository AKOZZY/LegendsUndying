#pragma once

#include "raylib.h"
#include "Entity.h"
#include "Collider.h"

class Projectile
{
public:
	void MoveX(float speed);
	void MoveY(float speed);
	void Move();
	void Draw();
	Vector2 position{};
	Vector2 firedDirection{};
	Texture2D sprite{};
	bool isActive{};
	float projSpeed{ 150 };
	Collider collider{};
	double damage{};
};

