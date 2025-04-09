#pragma once

#include "raylib.h"
#include "Collider.h"
#include "iostream"

class Entity
{
public:
	Entity();
	~Entity();

	// Methods
	void DrawSprite();
	void UpdatePosition(Vector2 position);
	void Hurt(double damage);
	void InvisibilityFrames();
	void Revive();
	void LoadSprites(Texture2D front, Texture2D back, Texture2D left, Texture2D right);
	void Animate();
	void SetDirection(Vector2 direction);
	void CheckIfDead();

	// Variables
	Vector2 position{};
	Vector2 direction{};
	int width{};
	int height{};
	Color color{};
	float speed{};

	// Sprites
	Texture2D current_sprite{};
	Texture2D front_sprite{};
	Texture2D back_sprite{};
	Texture2D left_sprite{};
	Texture2D right_sprite{};

	Texture2D dropShadow{};
	Collider collider{};

	int hp{};
	float iFrameTimer{};
	float iFrames{ 0.35 };
	bool hasBeenHit{};
	bool canBeHurt{ true };
	bool isDead{ false };

private:

};

