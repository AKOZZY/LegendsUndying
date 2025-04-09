#include "Item.h"

Item::Item()
{
}

void Item::SetItemSprite(Texture2D sprite)
{
	itemSprite = sprite;
}

void Item::DrawItem(float x, float y)
{
	DrawTextureEx(itemSprite, Vector2{ x, y }, 0, 3, WHITE);
}

