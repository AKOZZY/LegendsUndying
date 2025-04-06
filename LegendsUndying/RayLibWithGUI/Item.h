#pragma once

#include "raylib.h"
#include "Entity.h"
#include <string>


class Item
{
public:

	Item();
	void SetItemSprite(Texture2D sprite);
	void DrawItem(float x, float y);
	bool isStackable{};
	Vector2 position{};
	std::string itemName{};

private:
	Texture2D itemSprite{};
};

