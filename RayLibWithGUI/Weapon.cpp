#include "Weapon.h"

Weapon::Weapon()
{
	collider.Disable();
}

void Weapon::SetWeaponSprite(Texture2D sprite)
{
	weaponSprite = sprite;
}

Texture2D Weapon::GetWeaponSprite()
{
	return weaponSprite;
}

void Weapon::SetProjectileSprite(Texture2D sprite)
{
	projectileSprite = sprite;
}

Texture2D Weapon::GetProjectileSprite()
{
	return projectileSprite;
}

void Weapon::DrawWeapon(Vector2 position, Vector2 direction)
{
	// Weapon facing right 
	if(direction.x == 1) DrawTextureEx(weaponSprite, Vector2{ position.x + 25, position.y + 5 }, 90, 1, WHITE);

	// Weapon facing left
	if (direction.x == -1) DrawTextureEx(weaponSprite, Vector2{ position.x + -10, position.y + 20 }, -90, 1, WHITE);

	// Weapon facing down
	if (direction.y == 1) DrawTextureEx(weaponSprite, Vector2{ position.x + 15, position.y + 30 }, 180, 1, WHITE);

	// Weapon facing up
	if (direction.y == -1) DrawTextureEx(weaponSprite, Vector2{ position.x, position.y + -14 }, 0, 1, WHITE);
}

void Weapon::Attack(Vector2 position, Vector2 direction)
{
	// Weapon facing right 
	if (direction.x == 1) collider.UpdatePosition(Vector2{ position.x + 16, position.y});

	// Weapon facing left 
	if (direction.x == -1) collider.UpdatePosition(Vector2{ position.x - 16, position.y });

	// Weapon facing down 
	if (direction.y == 1) collider.UpdatePosition(Vector2{ position.x, position.y + 16 });

	// Weapon facing up 
	if (direction.y == -1) collider.UpdatePosition(Vector2{ position.x, position.y - 16 });
}
