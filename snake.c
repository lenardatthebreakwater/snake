#include "raylib.h"

int main(void) {
	int screenWidth = 1000;
	int screenHeight = 700;
	int playerSpeedX = 0;
	int playerSpeedY = 0;

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
		if (IsKeyPressed(KEY_RIGHT)) {
			playerSpeedX = 3;
		}
		if (IsKeyPressed(KEY_UP)) {
			playerSpeedX = 0;
			playerSpeedY = -3;
		}
		if (IsKeyPressed(KEY_LEFT)) {
			playerSpeedX = -3;
			playerSpeedY = 0;
		}
		if (IsKeyPressed(KEY_DOWN)) {
			playerSpeedX = 0;
			playerSpeedY = 3;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangleRec(player, RAYWHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
