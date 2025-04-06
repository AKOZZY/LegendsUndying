#pragma once
#include "raylib.h"
#include "Item.h"
#include <vector>

class InventorySlot
{
public:
	InventorySlot();
	void DrawSlot(float posX);
	int amountOfItemInSlot{};
	int stackSize{};
	bool full{};
private:
	Texture2D slot_sprite{};
};

