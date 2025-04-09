#pragma once
#include "raylib.h"
#include "iostream"

class Button
{
public:
	Button(std::string text, int fontSize, int width, int height, Vector2 position);
	~Button();
	void Draw();
	void MouseHover(Vector2 mousePosition);
	bool isMouseHover();
private:
	std::string text{};
	int fontSize{};
	int width{};
	int height{};
	Vector2 position{};
	Color color{ WHITE };
	Color selectedColor{ BLACK };
	bool isMouseOverButton{};
	Texture2D buttonSprite{};
};