#include "raylib.h"
#include "Button.h"

Button::Button(std::string text, int fontSize, int width, int height, Vector2 position)
{
	this->text = text;
	this->fontSize = fontSize;
	this->width = width;
	this->height = height;
	this->position = position;

	buttonSprite = LoadTexture("Assets/Button.png");
}

Button::~Button()
{
	UnloadTexture(buttonSprite);
}

void Button::Draw()
{
	if (!isMouseOverButton)
	{
		//DrawRectangle(position.x, position.y, width, height, color);
		DrawTextureEx(buttonSprite, Vector2{ position.x, position.y }, 0, 1, WHITE);
		DrawText(text.c_str(), position.x + 5, position.y + 5, fontSize, Color{ 251, 247, 160, 255 });
	}
	else
	{
		//DrawRectangle(position.x, position.y, width, height, selectedColor);
		DrawTextureEx(buttonSprite, Vector2{ position.x + 16, position.y }, 0, 1, GRAY);
		DrawText(text.c_str(), position.x + 21, position.y + 5, fontSize, Color{ 251, 247, 160, 150 });
	}
}

void Button::MouseHover(Vector2 mousePosition)
{
	if (mousePosition.x < position.x + width &&
		mousePosition.x > position.x &&
		mousePosition.y < position.y + height &&
		mousePosition.y > position.y)
	{
		isMouseOverButton = true;
	}
	else
	{
		isMouseOverButton = false;
	}
}

bool Button::isMouseHover()
{
	return isMouseOverButton;
}