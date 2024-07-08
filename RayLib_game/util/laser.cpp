#include "laser.h"


Laser::Laser(Vector2 p, int s) {
	this->position = p;
	this->speed = s;
	active = true;
}

void Laser::Update() {
	position.y += speed;
	if (active) {
		if (position.y < 25 || position.y > GetScreenHeight() - 100) {
			active = false;
		}
	}
}

void Laser::Draw() {
	if (active) {
		DrawRectangle(position.x, position.y, 1, 23, RED);
	}
}

Rectangle Laser::getRect() {
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 1;
	rect.height = 23;
	return rect;
}
