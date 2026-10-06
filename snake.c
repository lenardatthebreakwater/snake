#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define SCREENWIDTH 1000
#define SCREENHEIGHT 700
#define SNAKECHUNKWIDTH 40
#define SNAKECHUNKHEIGHT 40

typedef struct SnakeChunk {
	int x;
	int y;
} SnakeChunk;

typedef struct Node {
	SnakeChunk* data;
	struct Node* next;
} Node;

typedef struct LinkedList {
	struct Node* head;
	int length;
	int speedX;
	int speedY;
} LinkedList;

void addNode(LinkedList* linkedlist);

void freeLinkedList(LinkedList* linkedlist);

void printLinkedList(LinkedList* linkedlist);

void drawSnake(LinkedList* linkedlist);

void changeSnakeDirectionWhenKeyPressed(LinkedList* snake);

int main(void) {
	int screenWidth = SCREENWIDTH;
	int screenHeight = SCREENHEIGHT; 

	InitWindow(screenWidth, screenHeight, "Snake");
	SetTargetFPS(60);
	
	LinkedList snake = {
		.head = NULL,
		.length = 0,
		.speedX = 0,
		.speedY = 0
	};
	addNode(&snake);
	addNode(&snake);
	addNode(&snake);
	printLinkedList(&snake);
	
	while (!WindowShouldClose()) {
		Node* currentnode = snake.head;
		while (currentnode != NULL) {
			currentnode->data->x += snake.speedX;
			currentnode->data->y += snake.speedY;
			currentnode = currentnode->next;
		}

		changeSnakeDirectionWhenKeyPressed(&snake);
		
		BeginDrawing();
		ClearBackground(BLACK);
		drawSnake(&snake);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void addNode(LinkedList* linkedlist) {
	SnakeChunk* snakechunk = malloc(sizeof(SnakeChunk));
	snakechunk->x = ((SCREENWIDTH / 2) - (SNAKECHUNKWIDTH / 2)) - (SNAKECHUNKWIDTH * linkedlist->length);
	snakechunk->y = (SCREENHEIGHT / 2) - (SNAKECHUNKHEIGHT / 2);

	Node* newnode = malloc(sizeof(Node));
	newnode->data = snakechunk;

	newnode->next = linkedlist->head;
	linkedlist->head = newnode;
	linkedlist->length++;
}

void printLinkedList(LinkedList* linkedlist) {
	if (linkedlist->head == NULL) {
		printf("Empty");
		return;
	}

	Node* currentnode = linkedlist->head;

	while (currentnode != NULL) {
		printf("SnakeChunk{x: %d, y: %d} -> ", currentnode->data->x, currentnode->data->y);
		currentnode = currentnode->next;
	}
}

void drawSnake(LinkedList* snake) {
	Node* currentnode = snake->head;

	while (currentnode != NULL) {
		DrawRectangle(currentnode->data->x, currentnode->data->y, SNAKECHUNKWIDTH, SNAKECHUNKHEIGHT, RAYWHITE);
		currentnode = currentnode->next;
	}
}

void changeSnakeDirectionWhenKeyPressed(LinkedList* snake) {
	Node* currentnode = snake->head;
	
	while (currentnode != NULL) {
		if (IsKeyPressed(KEY_RIGHT)) {
			snake->speedX = 3;
			snake->speedY = 0;
		}
		if (IsKeyPressed(KEY_UP)) {
			snake->speedX = 0;
			snake->speedY = -3;
		}
		if (IsKeyPressed(KEY_LEFT)) {
			snake->speedX = -3;
			snake->speedY = 0;
		}
		if (IsKeyPressed(KEY_DOWN)) {
			snake->speedX = 0;
			snake->speedY = 3;
		}
		currentnode = currentnode->next;
	}
}

