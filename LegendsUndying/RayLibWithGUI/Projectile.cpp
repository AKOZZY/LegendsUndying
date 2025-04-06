#include "Projectile.h"

void Projectile::MoveX(float speed)
{
	position.x += speed * GetFrameTime();
}

void Projectile::MoveY(float speed)
{
	position.y += speed * GetFrameTime();
}

void Projectile::Move()
{
	if (firedDirection.x == 1) position.x += projSpeed * GetFrameTime();
	else if (firedDirection.x == -1) position.x -= projSpeed * GetFrameTime();
	else if (firedDirection.y == 1) position.y += projSpeed * GetFrameTime();
	else if (firedDirection.y == -1) position.y -= projSpeed * GetFrameTime();
	collider.UpdatePosition(position);
}

void Projectile::Draw()
{
	DrawTexture(sprite, position.x, position.y, WHITE);
}
