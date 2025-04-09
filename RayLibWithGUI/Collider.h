#pragma once

#include "raylib.h"

class Collider
{
public:

	Collider();

	void Enable();
	void Disable();

	void SetWidth(double value);
	void SetHeight(double value);

	void UpdatePosition(Vector2 position);

	double GetWidth();
	double GetHeight();
	Vector2 GetPosition();

	void DrawBox();

	bool canCollide{};
private:
	Vector2 position{};

	
	double width{};
	double height{};
};

