#include "InventorySlot.h"

InventorySlot::InventorySlot()
{
	slot_sprite = LoadTexture("Assets/InventorySlotFrame.png");
}

void InventorySlot::DrawSlot(float posX)
{
	//DrawTexture(slot_sprite, posX, 0, WHITE);

	DrawTextureEx(slot_sprite, Vector2{ posX, 736 }, 0, 4, Color{255, 255, 255, 255});
}

