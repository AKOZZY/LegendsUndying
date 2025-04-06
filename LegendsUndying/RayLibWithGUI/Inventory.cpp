#include "Inventory.h"

Inventory::Inventory()
{
	
}

void Inventory::RenderInventory()
{
	for (int i = 0; i < inventorySlots.size(); i++)
	{
		int x = i * 64;
		inventorySlots[i].DrawSlot(x);
	}
}

void Inventory::RenderItemsInInventory(std::vector<Item> items)
{
	for(int i = 0; i < items.size(); i++)
	{
		int x = i * 64;
		items[i].DrawItem(x + 8, 742);
	}
}

void Inventory::RenderCurrentWeapon(Weapon weapon)
{
	DrawTextureEx(weapon.GetWeaponSprite(), Vector2{ 740, 740, }, 45, 3, WHITE);
}

void Inventory::RenderWeaponSlot()
{
	weaponSlot.DrawSlot(737);
}
