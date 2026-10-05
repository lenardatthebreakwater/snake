#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define SCREENWIDTH 1000
#define SCREENHEIGHT 700

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
} LinkedList;

void addNode(LinkedList* linkedlist);

void freeLinkedList(LinkedList* linkedlist);

void printLinkedList(LinkedList* linkedlist); 

int main(void) {
	int screenWidth = SCREENWIDTH;
	int screenHeight = SCREENHEIGHT; 
	int snakeSpeedX = 0;
	int snakeSpeedY = 0;
	char direction;

	InitWindow(screenWidth, screenHeight, "Snake");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void addNode(LinkedList* linkedlist) {
	SnakeChunk* snakechunk = malloc(sizeof(SnakeChunk));
	snakechunk->x = ((SCREENWIDTH / 2) - (40 / 2)) - (40 * (linkedlist->length + 1));
	snakechunk->y = (SCREENHEIGHT / 2) - (40 / 2);

	Node* node = malloc(sizeof(Node));
	node->data = snakechunk;
	if (linkedlist->head != NULL) {
		node->next = linkedlist->head;
	}
	linkedlist->length += 1;
	linkedlist->head = node;
}

void PrintLinkedList(LinkedList* linkedlist) {
	if (linkedlist->head == NULL) {
		printf("Empty");
		return;
	}

	Node* currentNode = linkedlist->head;

	while (currentNode != NULL) {
		printf("SnakeChunk{%d, %d} -> ", currentNode->data->x, currentNode->data->y);
		currentNode = currentNode->next;
	}
}












