#include "Collider.h"

Collider::Collider()
{
	Enable();
	this->width = 16;
	this->height = 16;
}

void Collider::Enable()
{
	canCollide = true;
}

void Collider::Disable()
{
	canCollide = false;
}

void Collider::SetWidth(double value)
{
	width = value;
}

void Collider::SetHeight(double value)
{
	height = value;
}

void Collider::UpdatePosition(Vector2 position)
{
	this->position = position;
}

double Collider::GetWidth()
{
	return width;
}

double Collider::GetHeight()
{
	return height;
}

Vector2 Collider::GetPosition()
{
	return position;
}

void Collider::DrawBox()
{
	DrawRectangle(position.x, position.y, width, height, Color{ 255, 0, 0, 100 });
}


