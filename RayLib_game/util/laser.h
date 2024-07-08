#pragma once
#include "raylib.h"

class Laser {
private:
	Vector2 position;
	int speed;
public:
	bool active;
	Laser(Vector2 position, int s);
	void Update();
	void Draw();
	Rectangle getRect();

};