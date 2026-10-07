#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define SCREENWIDTH 1000
#define SCREENHEIGHT 700

typedef struct Node {
	int x;
	int y;
	struct Node* next;
} Node;

typedef struct LinkedList {
	Node* head;
	Node* last_node;
	int width;
	int height;
	int speed_x;
	int speed_y;
	int length;

} LinkedList;

void addNode(LinkedList* linked_list);

void freeLinkedList(LinkedList* linked_list);

void printLinkedList(LinkedList* linked_list);

void drawSnake(LinkedList* linked_list);

int main(void) {
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Snake");
	SetTargetFPS(60);
	
	LinkedList snake = {
		.head = NULL,
		.last_node = NULL,
		.width = 40,
		.height = 40,
		.speed_x = 0,
		.speed_y = 0,
		.length = 0
	};
	
	addNode(&snake);
	addNode(&snake);
	printLinkedList(&snake);
	
	while (!WindowShouldClose()) {
		Node* current_node = snake.head;
		while (current_node != NULL) {
			current_node->x += snake.speed_x;
			current_node->y += snake.speed_y;
			current_node = current_node->next;
		}

		if (IsKeyPressed(KEY_RIGHT)) {
			snake.speed_x = 3;
			snake.speed_y = 0;
		}
		if (IsKeyPressed(KEY_UP)) {
			snake.speed_x = 0;
			snake.speed_y = -3;
		}
		if (IsKeyPressed(KEY_LEFT)) {
			snake.speed_x = -3;
			snake.speed_y = 0;
		}
		if (IsKeyPressed(KEY_DOWN)) {
			snake.speed_x = 0;
			snake.speed_y = 3;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		drawSnake(&snake);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void addNode(LinkedList* linked_list) {
	Node* new_node = malloc(sizeof(Node));
	new_node->x = ((SCREENWIDTH / 2) - (40 / 2)) - (40 * linked_list->length);
	new_node->y = (SCREENHEIGHT / 2) - (40 / 2);
	new_node->next = NULL;
	
	if (linked_list->head == NULL) {
		linked_list->head = new_node;
		linked_list->length++;
		linked_list->last_node = new_node;
		return;
	}

	linked_list->last_node->next = new_node;
	linked_list->length++;
	linked_list->last_node = new_node;
}

void printLinkedList(LinkedList* linked_list) {
	if (linked_list->head == NULL) {
		printf("Empty");
		return;
	}

	Node* current_node = linked_list->head;

	while (current_node != NULL) {
		printf("Node {x: %d, y: %d} -> ", current_node->x, current_node->y);
		current_node = current_node->next;
	}
}

void drawSnake(LinkedList* snake) {
	Node* current_node = snake->head;

	while (current_node != NULL) {
		DrawRectangle(current_node->x, current_node->y, snake->width, snake->height, RAYWHITE);
		current_node = current_node->next;
	}
}


