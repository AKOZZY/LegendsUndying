#pragma once

#include "raylib.h"
#include "InventorySlot.h"
#include "Weapon.h"
#include <vector>

class Inventory
{
public:
	Inventory();
	std::vector<InventorySlot> inventorySlots{ 5 };
	void RenderInventory();
	void RenderItemsInInventory(std::vector<Item> items);
	void RenderCurrentWeapon(Weapon weapon);
	void RenderWeaponSlot();
private:
	InventorySlot weaponSlot{};
};

