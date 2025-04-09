#include "Entity.h"

Entity::Entity()
{
	this->width = 16;
	this->height = 16;
	this->color = WHITE;
	this->hp = 3;

	collider.SetWidth(width);
	collider.SetHeight(height);

	dropShadow = LoadTexture("Assets/DropShadow.png");
}

Entity::~Entity()
{
	UnloadTexture(dropShadow);
	UnloadTexture(front_sprite);
	UnloadTexture(back_sprite);
	UnloadTexture(left_sprite);
	UnloadTexture(right_sprite);
}

void Entity::DrawSprite()
{
	if (!isDead)
	{
		DrawTexture(dropShadow, position.x, position.y + 2, Color{ 255, 255, 255, 100 });
		if(canBeHurt) DrawTexture(current_sprite, position.x, position.y, WHITE);
		else DrawTexture(current_sprite, position.x, position.y, Color{255, 255, 255, 100});
		Animate();
	}
}

void Entity::UpdatePosition(Vector2 position)
{
	this->position = position;
	this->collider.UpdatePosition(position);
}

void Entity::Hurt(double damage)
{
	hasBeenHit = true;
	hp -= damage;
}

void Entity::InvisibilityFrames()
{
	if (hasBeenHit)
	{
		iFrameTimer += GetFrameTime();

		canBeHurt = false;

		if (iFrameTimer > iFrames)
		{
			iFrameTimer = 0;
			canBeHurt = true;
			hasBeenHit = false;
		}
	}
}

void Entity::Revive()
{
	this->isDead = false;
	this->hp = 3;
}

void Entity::LoadSprites(Texture2D front, Texture2D back, Texture2D left, Texture2D right)
{
	this->front_sprite = front;
	this->back_sprite = back;
	this->left_sprite = left;
	this->right_sprite = right;
}

void Entity::Animate()
{
	if (direction.x == -1) current_sprite = left_sprite;
	if (direction.x == 1) current_sprite = right_sprite;
	if (direction.y == -1) current_sprite = back_sprite;
	if (direction.y == 1) current_sprite = front_sprite;
}

void Entity::SetDirection(Vector2 direction)
{
	this->direction = direction;
}

void Entity::CheckIfDead()
{
	if (hp <= 0) isDead = true;
}
