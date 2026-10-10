#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define SCREENWIDTH 1200
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
	int length;

} LinkedList;

void addSnakeChunk(LinkedList* snake);

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
		.length = 0
	};
	
	Node snake_head = {
		.x = snake.chunk_side_length * 3,
		.y = snake.chunk_side_length * 3,
		.next = NULL
	};

	snake.head = &snake_head;
	snake.last_node = &snake_head;
	
	int x =  GetRandomValue(0, (SCREENWIDTH - snake.chunk_side_length));
	while (x % snake.chunk_side_length != 0) {
		x = GetRandomValue(0, (SCREENWIDTH - snake.chunk_side_length));
	}
	int y =  GetRandomValue(0, (SCREENHEIGHT - snake.chunk_side_length));
	while (y % snake.chunk_side_length != 0) {
			y = GetRandomValue(0, (SCREENHEIGHT - snake.chunk_side_length));
	}
	Node food = {
		.x = x,
		.y = y,
		.next = NULL,
	};

	int frame_count = 0;

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_RIGHT)) {
			snake.speed_x = snake.chunk_side_length;
			snake.speed_y = 0;
		}
		if (IsKeyPressed(KEY_UP)) {
			snake.speed_x = 0;
			snake.speed_y = -(snake.chunk_side_length);
		}
		if (IsKeyPressed(KEY_LEFT)) {
			snake.speed_x = -(snake.chunk_side_length);
			snake.speed_y = 0;
		}
		if (IsKeyPressed(KEY_DOWN)) {
			snake.speed_x = 0;
			snake.speed_y = snake.chunk_side_length;
		}
		
		Rectangle snake_head_rec = {
			.x=(float)snake_head.x,
			.y=(float)snake_head.y,
			.width=(float)snake.chunk_side_length,
			.height=(float)snake.chunk_side_length
		};

		Rectangle food_rec = {
			.x=(float)food.x,
			.y=(float)food.y,
			.width=(float)snake.chunk_side_length,
			.height=(float)snake.chunk_side_length
		};

		if (CheckCollisionRecs(snake_head_rec, food_rec)) {
			addSnakeChunk(&snake);

			food.x =  GetRandomValue(0, (SCREENWIDTH - snake.chunk_side_length));
			while (food.x % snake.chunk_side_length != 0) {
				food.x = GetRandomValue(0, (SCREENWIDTH - snake.chunk_side_length));
			}
			food.y =  GetRandomValue(0, (SCREENHEIGHT - snake.chunk_side_length));
			while (food.y % snake.chunk_side_length != 0) {
				food.y = GetRandomValue(0, (SCREENHEIGHT - snake.chunk_side_length));
			}
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

void addSnakeChunk(LinkedList* snake) {
	Node* new_node = malloc(sizeof(Node));
	new_node->x = snake->last_node->x;
	new_node->y = snake->last_node->y;
	new_node->next = NULL;

	snake->last_node->next = new_node;
	snake->length++;
	snake->last_node = new_node;
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

