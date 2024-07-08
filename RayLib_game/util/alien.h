#pragma once

#include "raylib.h"

class Alien {
private:

public:
	Alien(int type, Vector2 pos);
	void Update(int direction);
	void Draw();
	Rectangle getRect();
	int getType();
	static void unloadImages();

	static Texture2D alienImages[3];
	int type;
	Vector2 position;

};