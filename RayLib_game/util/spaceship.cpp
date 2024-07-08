#include "spaceship.h"

Spaceship::Spaceship() {
	image = LoadTexture("textures/opa.png");
	position.x = (GetScreenWidth() - image.width)/2 ;
	position.y = GetScreenHeight() - image.height - 100;
	laserFireTime = 0.0;
}

Spaceship::~Spaceship() {
	UnloadTexture(image);
}

void Spaceship::Draw() {
	DrawTextureV(image, position, WHITE);

	for (auto& l : lasers) {
		l.Draw();
	}
}

Rectangle Spaceship::getRect() {
	return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::MoveLeft() {
	position.x -= 3;
	if (position.x < 10) position.x = 10;
}

void Spaceship::MoveRight() {
	position.x += 3;
	if (position.x > GetScreenWidth() - image.width - 10) {
		position.x = GetScreenWidth() - image.width - 10;
	}
}

void Spaceship::reset() {
	position.x = (GetScreenWidth() - image.width) / 2;
	position.y = GetScreenHeight() - image.height;
	lasers.clear();
}

void Spaceship::Shoot() {
	if (GetTime() - laserFireTime >= 0.35) {
		lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y - 30 }, -7));
		laserFireTime = GetTime();
	}
}
