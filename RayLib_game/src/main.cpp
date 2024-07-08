#include <iostream>
#include <vector>
#include <string>
#include "../util/game.h"
#include "../util/obstacle.h"
#include "raylib.h"

using std::vector;

std::string formatWithLeadingZeros(int number, int width) {
	std::string numberText = std::to_string(number);
	int leadingZeros = width - numberText.length();
	return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() {


	InitWindow(1000, 800, "My window");
	SetTargetFPS(60);

	Color yellow = { 243, 216, 63, 255 };
	Texture2D background = LoadTexture("textures/back2.png");
	Texture2D spacheship = LoadTexture("textures/opa.png");
	Game game;
	Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		//DrawTexture(background, 0, 0, WHITE);
		DrawRectangleRoundedLines({ 10, 10, 980, 780 }, 0.18f, 20, 2, yellow);

		game.Update();
		game.handleInput();
		game.Draw();

		DrawLineEx({ 25, 700 }, { 975, 700 }, 3, yellow);
		float offset = 50;
		for (int i = 0; i < game.lives; i++) {
			DrawTextureV(spacheship, { offset, 730 }, WHITE);
			offset += 50;
		}
		if (game.run) {
			DrawTextEx(font, "LEVEL 01", { 770, 730 }, 34, 2, yellow);
		}
		else {
			DrawTextEx(font, "GAME OVER", { 770, 730 }, 34, 2, yellow);
		}
		DrawTextEx(font, "SCORE", { 50, 15}, 34, 2, yellow);
		std::string text = formatWithLeadingZeros(game.score, 5);
		DrawTextEx(font, "HIGH-SCORE", { 770, 15 }, 34, 2, yellow);
		std::string text1 = formatWithLeadingZeros(game.HIscore, 5);

		DrawTextEx(font, text.c_str(), { 50, 40 }, 34, 2, yellow);
		DrawTextEx(font, text1.c_str(), { 770, 40 }, 34, 2, yellow);
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}




