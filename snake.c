#include "raylib.h"

int main(void) {
	int screenWidth = 1000;
	int screenHeight = 700;
	int playerSpeedX = 0;
	int playerSpeedY = 0;
	char direction;

	InitWindow(screenWidth, screenHeight, "Snake");
	SetTargetFPS(60);
	
	Rectangle player = {
		.x = (screenWidth / 2) - (40 / 2),
		.y = (screenHeight / 2) - (40 / 2),
		.width = 40,
		.height = 40,
	};

	while (!WindowShouldClose()) {
		player.x += playerSpeedX;
		player.y += playerSpeedY;
		if (IsKeyPressed(KEY_RIGHT) && direction != 'l') {
			playerSpeedX = 3;
			playerSpeedY = 0;
			direction = 'r';
		}
		if (IsKeyPressed(KEY_UP) && direction != 'd') {
			playerSpeedX = 0;
			playerSpeedY = -3;
			direction = 'u';
		}
		if (IsKeyPressed(KEY_LEFT) && direction != 'r') {
			playerSpeedX = -3;
			playerSpeedY = 0;
			direction = 'l';
		}
		if (IsKeyPressed(KEY_DOWN) && direction != 'u') {
			playerSpeedX = 0;
			playerSpeedY = 3;
			direction = 'd';
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangleRec(player, RAYWHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
