#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define SCREENWIDTH 1000
#define SCREENHEIGHT 800

typedef struct Node {
	int x;
	int y;
	struct Node* next;
} Node;

typedef struct LinkedList {
	Node* head;
	Node* last_node;
	int chunk_side_length;
	int speed_x;
	int speed_y;
	char direction;
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
		.chunk_side_length = 40,
		.speed_x = 0,
		.speed_y = 0,
		.direction = 0,
		.length = 0
	};
	
	addNode(&snake);
	
	Node food = {
		.x = GetRandomValue(0, (SCREENWIDTH - snake.chunk_side_length)),
		.y = GetRandomValue(0, (SCREENHEIGHT - snake.chunk_side_length)),
		.next = NULL,
	};

	int frame_count = 0;

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_RIGHT) && snake.direction != 'l') {
			snake.speed_x = snake.chunk_side_length;
			snake.speed_y = 0;
			snake.direction = 'r';
		}
		if (IsKeyPressed(KEY_UP) && snake.direction != 'd') {
			snake.speed_x = 0;
			snake.speed_y = -(snake.chunk_side_length);
			snake.direction = 'u';
		}
		if (IsKeyPressed(KEY_LEFT) && snake.direction != 'r') {
			snake.speed_x = -(snake.chunk_side_length);
			snake.speed_y = 0;
			snake.direction = 'l';
		}
		if (IsKeyPressed(KEY_DOWN) && snake.direction != 'u') {
			snake.speed_x = 0;
			snake.speed_y = snake.chunk_side_length;
			snake.direction = 'd';
		}


		frame_count++;
		
		if (frame_count == 10) {
			frame_count = 0;
			
			int prev_x = snake.head->x;
			int prev_y = snake.head->y;

			snake.head->x += snake.speed_x;
			snake.head->y += snake.speed_y;
			
			Node* current_node = snake.head->next;
			while (current_node != NULL) {
				int temp_x = current_node->x;
				int temp_y = current_node->y;

				current_node->x = prev_x;
				current_node->y = prev_y;

				prev_x = temp_x;
				prev_y = temp_y;

				current_node = current_node->next;
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawRectangle(food.x, food.y, snake.chunk_side_length, snake.chunk_side_length, RAYWHITE);
		drawSnake(&snake);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void addNode(LinkedList* linked_list) {
	Node* new_node = malloc(sizeof(Node));
	new_node->x = ((SCREENWIDTH / 2) - (linked_list->chunk_side_length / 2));
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
		DrawRectangle(current_node->x, current_node->y, snake->chunk_side_length, snake->chunk_side_length, RAYWHITE);
		current_node = current_node->next;
	}
}


